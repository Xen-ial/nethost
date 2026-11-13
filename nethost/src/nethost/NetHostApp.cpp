#include "nethost/ErrorCodes.h"
#include <nethost/NetHostApp.h>
#include <nethost/Utils.h>
#include <nethost/Log.h>

#include <nethost.h>
#include <coreclr_delegates.h>
#include <hostfxr.h>

#include <array>
#include <cstdio>
#include <dlfcn.h>
#include <cassert>
#include <print>
#include <fstream>
#include <format>
#include <filesystem>

namespace
{
	constexpr std::uint32_t MAX_PATH               = 260;
	const std::string       DEFAULT_RUNTIME_CONFIG = R"(
{
  "runtimeOptions": {
    "tfm": "net10.0",
    "rollForward": "LatestMinor",
    "framework": {
      "name": "Microsoft.NETCore.App",
      "version": "10.0.0"
    },
    "configProperties": {
      "System.Runtime.Serialization.EnableUnsafeBinaryFormatterSerialization": false
    }
  }
}
)";
} // namespace

namespace nethost
{
	NetHostApp::NetHostApp(const std::string& runtimeConfigPath)
	    : m_isInitialized(loadHostFXR(runtimeConfigPath))
	{
		if (!m_isInitialized)
			err::logln("failed to load host FXR", err::StatusCode::HOST_INVALID_STATE);
	}

	NetHostApp::NetHostApp()
	{
		std::ofstream defaultRuntime("Default.runtimeconfig.json");
		if (!defaultRuntime.is_open())
		{
			err::logln("failed to create default runtime config.", err::StatusCode::INVALID_CONFIG_FILE);
			m_isInitialized = false;
			return;
		}

		defaultRuntime << DEFAULT_RUNTIME_CONFIG;
		defaultRuntime.close();

		bool hostFXR = loadHostFXR("Default.runtimeconfig.json");
		if (!hostFXR)
		{
			err::logln("failed to load host FXR", err::StatusCode::HOST_INVALID_STATE);
			m_isInitialized = false;
			return;
		}

		std::filesystem::path defaultRuntimeConfigpath = "Default.runtimeconfig.json";
		std::filesystem::remove(defaultRuntimeConfigpath);

		m_isInitialized = true;
	}

	void NetHostApp::shutdown()
	{
		m_close(m_hostContext);
	}

	bool NetHostApp::loadHostFXR(const std::string& runtimeConfigPath)
	{
		std::array<char, MAX_PATH> buffer{};
		std::size_t                bufferSize = sizeof(buffer) / sizeof(char);

		int hostHandle = get_hostfxr_path(buffer.data(), &bufferSize, nullptr);
		if (hostHandle != 0)
			return false;

		void* lib = loadLibrary(buffer.data());

		m_initForRuntimeConfig = reinterpret_cast<InitForRuntimeConfigFunc>(
		    getExport(lib, "hostfxr_initialize_for_runtime_config"));

		m_getRuntimeDelegate = reinterpret_cast<GetRuntimeDelegateFunc>(
		    getExport(lib, "hostfxr_get_runtime_delegate"));

		m_close = reinterpret_cast<CloseFunc>(
		    getExport(lib, "hostfxr_close"));

		int result = m_initForRuntimeConfig(runtimeConfigPath.c_str(),
		    nullptr, &m_hostContext);

		if (result != 0 || m_hostContext == nullptr)
		{
			err::logln("failed to initialize", err::fromFXR(result));
			m_close(m_hostContext);
			return false;
		}

		result = m_getRuntimeDelegate(
		    m_hostContext,
		    hdt_load_assembly,
		    &lib);

		if (result != 0 || lib == nullptr)
		{
			err::logln("failed to resolve (loadAssembly) pointer", err::fromFXR(result));
			return false;
		}

		m_loadAssembly = reinterpret_cast<LoadAssemblyFunc>(lib);
		if (m_loadAssembly == nullptr)
			return false;

		result = m_getRuntimeDelegate(
		    m_hostContext,
		    hdt_load_assembly_bytes,
		    &lib);

		if (result != 0 || lib == nullptr)
		{
			err::logln("failed to resolve (loadAssemblyBytes) pointer", err::fromFXR(result));
			return false;
		}

		m_loadAssemblyBytes = reinterpret_cast<LoadAssemblyBytesFunc>(lib);
		if (m_loadAssemblyBytes == nullptr)
			return false;

		result = m_getRuntimeDelegate(
		    m_hostContext,
		    hdt_get_function_pointer,
		    &lib);

		if (result != 0 || lib == nullptr)
		{
			err::logln("failed to resolve (getFunction)", err::fromFXR(result));
			return false;
		}

		m_getFunctionPointer = reinterpret_cast<GetFunctionPointerFunc>(lib);
		if (m_getFunctionPointer == nullptr)
			return false;

		return ((m_initForRuntimeConfig != nullptr) && (m_getRuntimeDelegate != nullptr) && (m_close != nullptr));
	}

	Func NetHostApp::getFunc(const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib) const
	{
		auto getFunction = this->m_getFunctionPointer;

		void* function = nullptr;
		int   result   = getFunction(
		    std::format("{}.{}, {}", nameSpace, targetClass, targetLib).c_str(),
		    name.c_str(),
		    nullptr,
		    nullptr,
		    nullptr,
		    &function);

		if (result != 0 || function == nullptr)
			return nullptr;

		return reinterpret_cast<Func>(function);
	}

	void NetHostApp::getFuncDelegate(void** delegate, const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib)
	{
		auto getFunction = this->m_getFunctionPointer;

		int result = getFunction(
		    std::format("{}.{}, {}", nameSpace, targetClass, targetLib).c_str(),
		    name.c_str(),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    nullptr,
		    *&delegate);

		if (result != 0 || delegate == nullptr)
			delegate = nullptr;
	}

	bool NetHostApp::initForRuntimeConfig(const char* runtimeConfigPath, const struct hostfxr_initialize_parameters* parameters)
	{
		int success = m_initForRuntimeConfig(runtimeConfigPath, parameters, &m_hostContext);
		return success == 0;
	}

	bool NetHostApp::getRuntimeDelegate(int hostFXRDelegateType, void* pData)
	{
		int success = m_getRuntimeDelegate(m_hostContext, hostFXRDelegateType, &pData);
		return success == 0;
	}

	bool NetHostApp::closeApp()
	{
		int success = m_close(m_hostContext);
		return success == 0;
	}

	bool NetHostApp::loadAssembly(const char* path, void* loadContext, void* reserved)
	{
		int success = m_loadAssembly(path, loadContext, reserved);
		return success != 0;
	}

	bool NetHostApp::loadAssembly(const std::vector<std::byte>& assembly, const std::vector<std::byte>& symbols, void* loadContext, void* reserved)
	{
		int success = m_loadAssemblyBytes(assembly.data(), assembly.size(), symbols.data(), symbols.size(), loadContext, reserved);
		return success != 0;
	}
} // namespace nethost