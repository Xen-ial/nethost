#pragma once
#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>
#include <nethost/Utils.h>

namespace scripting
{
	/**
	 * @brief Forwards functions to the .NET assembly
	 */
	struct ForwardFuncInfo
	{
		void* pTestFn{nullptr};
	};

	class NativeBridge
	{
	public:
		NativeBridge(const NativeBridge&)            = default;
		NativeBridge& operator=(const NativeBridge&) = default;

		NativeBridge(NativeBridge&&)            = delete;
		NativeBridge& operator=(NativeBridge&&) = delete;

		NativeBridge(nethost::BorrowedRef<nethost::NetHostApp> app);
		~NativeBridge();

		void createScriptingDomain();
		void destroyScriptingDomain();

		void loadAssembly(const std::string& path);
		void loadAssemblyRelative(const std::string& path);

		void forwardFunctions(ForwardFuncInfo& info);

		void createEntity(int entityId);
		void destroyEntity(int entityId);
		void printAllEntities();
		void updateScripts();

		void addScript(int entityId, std::string& scriptName);

		[[nodiscard]] nethost::Assembly getLib() const { return m_libNativeBridge; }
		[[nodiscard]] bool              hasAssemblyLoaded() const { return m_libNativeBridge.hasAssemblyLoaded() && m_hasResolvedFNS; }

	private:
		nethost::BorrowedRef<nethost::NetHostApp> m_app;
		nethost::Assembly                         m_libNativeBridge;

		using EmptyVoid              = void(NETHOST_DELEGATE_CALLTYPE*)();
		using LoadAssembly           = unsigned char(NETHOST_DELEGATE_CALLTYPE*)(const char*);
		using InitializeNativeBridge = int(NETHOST_DELEGATE_CALLTYPE*)(void* initTestCall);
		using CreateEntity           = void(NETHOST_DELEGATE_CALLTYPE*)(int);
		using DestroyEntity          = void(NETHOST_DELEGATE_CALLTYPE*)(int);
		using AddScript              = void(NETHOST_DELEGATE_CALLTYPE*)(int, const char*);

		EmptyVoid m_createScriptingDomain{nullptr};
		EmptyVoid m_destroyScriptingDomain{nullptr};

		LoadAssembly           m_loadAssembly{nullptr};
		InitializeNativeBridge m_initNativeBridge{nullptr};

		CreateEntity  m_createEntity{nullptr};
		DestroyEntity m_destroyEntity{nullptr};
		EmptyVoid     m_printAllEntities{nullptr};
		EmptyVoid     m_updateScripts{nullptr};

		AddScript m_addScript{nullptr};

		bool m_hasResolvedFNS{};

		void loadFunctions();
	};
} // namespace scripting