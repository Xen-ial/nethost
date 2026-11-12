#pragma once
#include <nethost/Utils.h>

#include <cstddef>
#include <string>
#include <vector>

namespace nethost
{
	using Func        = int(NETHOST_DELEGATE_CALLTYPE*)(void*, int);
	using HostContext = void*;

	class Assembly;

	class NetHostApp
	{
	public:
		NetHostApp(const NetHostApp&)            = default;
		NetHostApp& operator=(const NetHostApp&) = default;

		NetHostApp(NetHostApp&&)            = default;
		NetHostApp& operator=(NetHostApp&&) = default;

		NetHostApp(const std::string& runtimeConfigPath);
		NetHostApp();

		~NetHostApp() = default;

		void shutdown();

		[[nodiscard]] bool isInititalized() const { return m_isInitialized; }

	protected:
		friend class Assembly;

		[[nodiscard]] Func getFunc(const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib) const;
		void               getFuncDelegate(void** delegate, const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib);

		bool initForRuntimeConfig(const char* runtimeConfigPath, const struct hostfxr_initialize_parameters* parameters);

		bool getRuntimeDelegate(int hostFXRDelegateType, void* pData);
		bool closeApp();

		bool loadAssembly(const char* path, void* loadContext = nullptr, void* reserved = nullptr);
		bool loadAssembly(const std::vector<std::byte>& assembly, const std::vector<std::byte>& symbols = {}, void* loadContext = nullptr, void* reserved = nullptr);

		[[nodiscard]] HostContext getHostContext() const { return m_hostContext; }

	private:
		using InitForRuntimeConfigFunc = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, const struct hostfxr_initialize_parameters*, void**);
		using GetRuntimeDelegateFunc   = int(NETHOST_DELEGATE_CALLTYPE*)(void* const, int hostfxr_delegate_type, void**);
		using CloseFunc                = int(NETHOST_DELEGATE_CALLTYPE*)(void* const);
		using LoadAssemblyFunc         = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, void*, void*);
		using LoadAssemblyBytesFunc    = int(NETHOST_DELEGATE_CALLTYPE*)(const void*, unsigned long, const void*, unsigned long, void*, void*);
		using GetFunctionPointerFunc   = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, const char*, const char*, void*, void*, void**);

		HostContext m_hostContext = nullptr;

		InitForRuntimeConfigFunc m_initForRuntimeConfig = nullptr;
		GetRuntimeDelegateFunc   m_getRuntimeDelegate   = nullptr;
		CloseFunc                m_close                = nullptr;
		LoadAssemblyFunc         m_loadAssembly         = nullptr;
		LoadAssemblyBytesFunc    m_loadAssemblyBytes    = nullptr;
		GetFunctionPointerFunc   m_getFunctionPointer   = nullptr;

		bool m_isInitialized{};

		bool loadHostFXR(const std::string& runtimeConfigPath);
	};
} // namespace nethost