#include "scripting/NativeBridge.h"
#include <print>
#include <scripting/ScriptHost.h>

#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

namespace
{
	struct FuncData
	{
		void* pTestFn{nullptr};
	};
} // namespace

namespace scripting
{
	ScriptHost::ScriptHost()
	{
		if (!init())
			std::println("Failed to load script host.");
	}

	ScriptHost::~ScriptHost()
	{
		if (m_nethostApp.isInititalized())
			m_nethostApp.shutdown();
	}

	void ScriptHost::loadAssembly(const std::string& path)
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->loadAssembly(path);
	}

	void ScriptHost::loadAssemblyRelative(const std::string& path)
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->loadAssemblyRelative(path);
	}

	void ScriptHost::createEntity(int entityId)
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->createEntity(entityId);
	}

	void ScriptHost::destroyEntity(int entityId)
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->destroyEntity(entityId);
	}

	void ScriptHost::printAllEntities()
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->printAllEntities();
	}

	void ScriptHost::updateScripts()
	{
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return;

		m_nativeBridge->updateScripts();
	}

	bool ScriptHost::init()
	{
		m_nativeBridge.emplace(m_nethostApp);
		if (!m_nativeBridge.has_value() || !m_nativeBridge->hasAssemblyLoaded())
			return false;

		m_nativeBridge->createScriptingDomain();
		ForwardFuncInfo funcInfo{};

		// m_nativeBridge->forwardFunctions(funcInfo);
		return true;
	}
} // namespace scripting