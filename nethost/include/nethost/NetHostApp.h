#pragma once
#include <cstddef>
#include <string>
#include <vector>

#if defined(_WIN32)
#define NETHOST_DELEGATE_CALLTYPE __stdcall
#else
#define NETHOST_DELEGATE_CALLTYPE
#endif

#if defined(_MSC_VER)
#define NETHOST_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#if defined(__i386__)
#define NETHOST_CDECL __attribute__((cdecl))
#else
#define NETHOST_CDECL
#endif
#else
#define NETHOST_CDECL
#endif

namespace nethost
{
	using Func        = int (*)(void*, int);
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
		using InitForRuntimeConfigFunc = int (*)(const char*, const struct hostfxr_initialize_parameters*, void**);
		using GetRuntimeDelegateFunc   = int (*)(void* const, int hostfxr_delegate_type, void**);
		using CloseFunc                = int (*)(void* const);
		using LoadAssemblyFunc         = int (*)(const char*, void*, void*);
		using LoadAssemblyBytesFunc    = int (*)(const void*, unsigned long, const void*, unsigned long, void*, void*);
		using GetFunctionPointerFunc   = int (*)(const char*, const char*, const char*, void*, void*, void**);

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