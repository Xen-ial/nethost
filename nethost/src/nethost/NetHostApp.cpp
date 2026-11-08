#include <nethost/NetHostApp.h>
#include <nethost/Utils.h>

#include <nethost.h>
#include <coreclr_delegates.h>
#include <hostfxr.h>

#include <array>
#include <cstdio>
#include <dlfcn.h>
#include <cassert>
#include <print>

namespace
{
	constexpr std::uint32_t MAX_PATH = 260;
}

namespace nethost
{
	NetHostApp::NetHostApp(const std::string& runtimeConfigPath)
	    : m_isInitialized(loadHostFXR(runtimeConfigPath))
	{
		if (!m_isInitialized)
		{
			std::println("failed to load host FXR");
			return;
		}
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
			std::println("failed to initialize");
			m_close(m_hostContext);
			return false;
		}

		result = m_getRuntimeDelegate(
		    m_hostContext,
		    hdt_load_assembly,
		    &lib);

		if (result != 0 || lib == nullptr)
		{
			std::println("failed to resolve (loadAssembly) pointer");
			return false;
		}

		m_loadAssembly = reinterpret_cast<LoadAssemblyFunc>(lib);
		if (m_loadAssembly == nullptr)
			return false;

		result = m_getRuntimeDelegate(
		    m_hostContext,
		    hdt_get_function_pointer,
		    &lib);

		if (result != 0 || lib == nullptr)
		{
			std::println("failed to resolve (getFunction)");
			return false;
		}

		m_getFunctionPointer = reinterpret_cast<GetFunctionPointerFunc>(lib);
		if (m_getFunctionPointer == nullptr)
			return false;

		return ((m_initForRuntimeConfig != nullptr) && (m_getRuntimeDelegate != nullptr) && (m_close != nullptr));
	}

	Func NetHostApp::getFunc(const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib) const
	{
		auto getFunction = this->getFunction();

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
		auto getFunction = this->getFunction();

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
} // namespace nethost