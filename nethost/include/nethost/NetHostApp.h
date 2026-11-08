#pragma once
#include <string>

#if defined(_WIN32)
#define NETHOST_DELEGATE_CALLTYPE __stdcall
#else
#define NETHOST_DELEGATE_CALLTYPE
#endif

namespace nethost
{
	using InitForRuntimeConfigFunc = int (*)(const char*, const struct hostfxr_initialize_parameters*, void**);
	using GetRuntimeDelegateFunc   = int (*)(void* const, int hostfxr_delegate_type, void**);
	using CloseFunc                = int (*)(void* const);
	using LoadAssemblyFunc         = int (*)(const char*, void*, void*);
	using GetFunctionPointerFunc   = int (*)(const char*, const char*, const char*, void*, void*, void**);
	using HostContext              = void*;
	using Func                     = int (*)(void*, int);

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

		void getFuncDelegate(void** delegate, const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib);

		[[nodiscard]] HostContext              getHostContext() const { return m_hostContext; }
		[[nodiscard]] InitForRuntimeConfigFunc getInitForRuntimeConfig() const { return m_initForRuntimeConfig; };
		[[nodiscard]] GetRuntimeDelegateFunc   getRuntimeDelegate() const { return m_getRuntimeDelegate; }
		[[nodiscard]] CloseFunc                getCloseFunc() const { return m_close; }
		[[nodiscard]] LoadAssemblyFunc         getLoadAssembly() const { return m_loadAssembly; }
		[[nodiscard]] GetFunctionPointerFunc   getFunction() const { return m_getFunctionPointer; }

	private:
		InitForRuntimeConfigFunc m_initForRuntimeConfig = nullptr;
		GetRuntimeDelegateFunc   m_getRuntimeDelegate   = nullptr;
		CloseFunc                m_close                = nullptr;
		LoadAssemblyFunc         m_loadAssembly         = nullptr;
		GetFunctionPointerFunc   m_getFunctionPointer   = nullptr;

		HostContext m_hostContext = nullptr;

		bool m_isInitialized{};

		bool loadHostFXR(const std::string& runtimeConfigPath);
	};
} // namespace nethost