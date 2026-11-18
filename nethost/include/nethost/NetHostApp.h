#pragma once
#include <nethost/Utils.h>

#include <cstddef>
#include <string>
#include <vector>

namespace nethost
{
	class Assembly;
	class NetClass;

	/**
	 * @brief Native host FXR context wrapper. Spins up a new host context, and resolves all needed function pointers
	 * This app context is needed for the rest of the library to work. There can be multiple running within the same application.
	 */
	class NetHostApp
	{
	public:
		NetHostApp(const NetHostApp&)            = default;
		NetHostApp& operator=(const NetHostApp&) = default;

		NetHostApp(NetHostApp&&)            = default;
		NetHostApp& operator=(NetHostApp&&) = default;

		/**
		 * @brief Creates a new host app, with a target .net app.runtimeconfig.json
		 * @param runtimeConfigPath Runtime config json path
		 */
		NetHostApp(const std::string& runtimeConfigPath);

		/**
		 * @brief Creates a new host app, with a default .NET 10 runtime config
		 * Auto loads the context with C# .Net 10 as the target runtime environment
		 */
		NetHostApp();

		~NetHostApp() = default;

		/**
		 * @brief Cleans up the runtime application resources
		 */
		void shutdown();

		/**
		 * @brief Ensures that the application context is properly initialized
		 * @return true App is initialized
		 * @return false App has not been initialized
		 */
		[[nodiscard]] bool isInititalized() const { return m_isInitialized; }

	protected:
		friend class Assembly;
		friend class NetClass;

		/**
		 * @brief Get target function from a library, and class
		 * @param name Target method name
		 * @param nameSpace Target class namespace
		 * @param targetClass Target class name
		 * @param targetLib Target library name
		 * @return Func Empty void function
		 */
		[[nodiscard]] Func getFunc(const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib) const;

		/**
		 * @brief Get target delegate function from a library, and class
		 * @param delegate Delegate definition
		 * @param name Target method name
		 * @param nameSpace Target class namespace
		 * @param targetClass Target class name
		 * @param targetLib Target library name
		 */
		void getFuncDelegate(void** delegate, const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib);

		/**
		 * @brief Initialize the host FXR runtime
		 * @param runtimeConfigPath Target runtime config
		 * @param parameters Target input params
		 * @return true Successfully initialized runtime
		 * @return false Failed to initialize runtime
		 */
		bool initForRuntimeConfig(const char* runtimeConfigPath, const struct hostfxr_initialize_parameters* parameters);

		/**
		 * @brief Get a delegate from the host runtime
		 * @param hostFXRDelegateType Target delegate from host
		 * @param pData Pointer to fill
		 * @return true Successfully got host runtime delegate
		 * @return false Failed to get host runtime delegate
		 */
		bool getRuntimeDelegate(int hostFXRDelegateType, void* pData);

		/**
		 * @brief Close the host FXR context / Application
		 * @return true Successfully closed application
		 * @return false Failed to close application or it is already closed
		 */
		bool closeApp();

		/**
		 * @brief Loads a managed assembly from a disk path
		 * @param path Target assembly path
		 * @param loadContext AssemblyContext to load into
		 * @param reserved Extra information
		 * @return true Loaded assembly successfully
		 * @return false Failed to load assembly
		 */
		bool loadAssembly(const char* path, void* loadContext = nullptr, void* reserved = nullptr);

		/**
		 * @brief  Loads managed assembly from in memory bytes, with an option to pass symbol information
		 * @param assembly Target managed assembly bytes
		 * @param symbols Target managed assembly debug symbol bytes
		 * @param loadContext AssemblyContext to load into
		 * @param reserved Extra information
		 * @return true Loaded assembly successfully
		 * @return false Failed to load assembly
		 */
		bool loadAssembly(const std::vector<std::byte>& assembly, const std::vector<std::byte>& symbols = {}, void* loadContext = nullptr, void* reserved = nullptr);

		/**
		 * @brief Get the Host Context
		 * @return HostContext Application FXR host context handle
		 */
		[[nodiscard]] HostContext getHostContext() const { return m_hostContext; }

	private:
		using InitForRuntimeConfigFunc = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, const struct hostfxr_initialize_parameters*, void**);
		using GetRuntimeDelegateFunc   = int(NETHOST_DELEGATE_CALLTYPE*)(void* const, int hostfxr_delegate_type, void**);
		using CloseFunc                = int(NETHOST_DELEGATE_CALLTYPE*)(void* const);
		using LoadAssemblyFunc         = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, void*, void*);
		using LoadAssemblyBytesFunc    = int(NETHOST_DELEGATE_CALLTYPE*)(const void*, unsigned long, const void*, unsigned long, void*, void*);
		using GetFunctionPointerFunc   = int(NETHOST_DELEGATE_CALLTYPE*)(const char*, const char*, const char*, void*, void*, void**);
		using HostFXRErrorCallbackFunc = void(NETHOST_DELEGATE_CALLTYPE* (*)(void (*)(const char*)))(const char*);

		HostContext m_hostContext = nullptr;

		InitForRuntimeConfigFunc m_initForRuntimeConfig = nullptr;
		GetRuntimeDelegateFunc   m_getRuntimeDelegate   = nullptr;
		CloseFunc                m_close                = nullptr;
		LoadAssemblyFunc         m_loadAssembly         = nullptr;
		LoadAssemblyBytesFunc    m_loadAssemblyBytes    = nullptr;
		GetFunctionPointerFunc   m_getFunctionPointer   = nullptr;
		HostFXRErrorCallbackFunc m_hostFXRErrorCallback = nullptr;

		bool m_isInitialized{};

		/**
		 * @brief Loads the host FXR into native memory
		 * @param runtimeConfigPath Target .Net runtime version config path
		 * @return true Successfully loaded host FXR
		 * @return false Failed to load host FXR
		 */
		bool loadHostFXR(const std::string& runtimeConfigPath);
	};
} // namespace nethost