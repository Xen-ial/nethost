#include <scripting/NativeBridge.h>

#include <stdexcept>
#include <filesystem>

namespace scripting
{
	NativeBridge::NativeBridge(nethost::BorrowedRef<nethost::NetHostApp> app)
	    : m_app(app), m_libNativeBridge(m_app, "NativeBridge.dll", "NativeBridge")
	{
		if (!m_app.get().isInititalized())
			throw std::runtime_error("failed to load NativeBridge nethost app is not initialized.");

		if (!m_libNativeBridge.hasAssemblyLoaded())
			throw std::runtime_error("failed to load NativeBridge assembly failed to initialize.");

		loadFunctions();
	}

	NativeBridge::~NativeBridge()
	{
		if (m_destroyScriptingDomain != nullptr)
			m_destroyScriptingDomain();
	}

	void NativeBridge::loadFunctions()
	{
		m_createScriptingDomain = m_libNativeBridge.getFunc<EmptyVoid>(
		    "CreateScriptingDomain", "NativeBridge", "Entry");

		if (m_createScriptingDomain == nullptr)
			throw std::runtime_error("NativeHost: Missing function CreateScriptingDomain().");

		m_destroyScriptingDomain = m_libNativeBridge.getFunc<EmptyVoid>(
		    "DestroyScriptingDomain", "NativeBridge", "Entry");

		if (m_destroyScriptingDomain == nullptr)
			throw std::runtime_error("NativeHost: Missing function DestroyScriptingDomain().");

		m_loadAssembly = m_libNativeBridge.getFunc<LoadAssembly>(
		    "LoadAssembly", "NativeBridge", "Entry");

		if (m_loadAssembly == nullptr)
			throw std::runtime_error("NativeHost: Missing function LoadAssembly().");

		m_initNativeBridge = m_libNativeBridge.getFunc<InitializeNativeBridge>(
		    "Initialize", "NativeBridge", "Entry");

		if (m_initNativeBridge == nullptr)
			throw std::runtime_error("NativeHost: Missing function InitNativeBridge().");

		m_createEntity = m_libNativeBridge.getFunc<CreateEntity>(
		    "CreateEntity", "NativeBridge", "Entry");

		if (m_createEntity == nullptr)
			throw std::runtime_error("NativeHost: Missing function CreateEntity");

		m_destroyEntity = m_libNativeBridge.getFunc<DestroyEntity>(
		    "DestroyEntity", "NativeBridge", "Entry");

		if (m_destroyEntity == nullptr)
			throw std::runtime_error("NativeHost: Missing function DestroyEntity");

		m_printAllEntities = m_libNativeBridge.getFunc<EmptyVoid>(
		    "PrintAllEntities", "NativeBridge", "Entry");

		if (m_printAllEntities == nullptr)
			throw std::runtime_error("NativeHost: Missing function PrintAllEntities");

		m_updateScripts = m_libNativeBridge.getFunc<EmptyVoid>(
		    "UpdateScripts", "NativeBridge", "Entry");

		if (m_updateScripts == nullptr)
			throw std::runtime_error("NativeHost: Missing function UpdateScripts");

		m_hasResolvedFNS = true;
	}

	void NativeBridge::createScriptingDomain()
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_createScriptingDomain();
	}

	void NativeBridge::destroyScriptingDomain()
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_destroyScriptingDomain();
	}

	void NativeBridge::loadAssembly(const std::string& path)
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_loadAssembly(path.c_str());
	}

	void NativeBridge::loadAssemblyRelative(const std::string& path)
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		auto targetAssembly = std::filesystem::absolute(path);
		m_loadAssembly(targetAssembly.c_str());
	}

	void NativeBridge::forwardFunctions(ForwardFuncInfo& info)
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		if (m_initNativeBridge(&info) != 0)
			throw std::runtime_error("NativeHost: Failed to forward functions.");
	}

	void NativeBridge::createEntity(int entityId)
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_createEntity(entityId);
	}

	void NativeBridge::destroyEntity(int entityId)
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_destroyEntity(entityId);
	}

	void NativeBridge::printAllEntities()
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_printAllEntities();
	}

	void NativeBridge::updateScripts()
	{
		if (!hasAssemblyLoaded())
			throw std::runtime_error("NativeHost: Assembly is not initialized.");

		m_updateScripts();
	}
} // namespace scripting