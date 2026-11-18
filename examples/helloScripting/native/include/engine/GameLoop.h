#pragma once
#include "nethost/Utils.h"
#include <scripting/ScriptHost.h>

#include <string>
#include <unordered_set>

namespace engine
{
	class Entity
	{
	public:
		Entity(int eId, nethost::BorrowedRef<scripting::ScriptHost> scriptHost)
		    : m_eId(eId), m_scriptHost(scriptHost) {}

		void addNetComponent(const std::string& compName);
		void addNetScript(const std::string& scrName);

		void removeNetComponent(const std::string& compName);
		void removeNetScript(const std::string& scrName);

		[[nodiscard]] int                             entId() const { return m_eId; }
		[[nodiscard]] std::unordered_set<std::string> getNetScripts() const { return m_netScripts; }

	private:
		int m_eId;

		std::unordered_set<std::string> m_netComponents;
		std::unordered_set<std::string> m_netScripts;

		nethost::BorrowedRef<scripting::ScriptHost> m_scriptHost;
		// C++ Components, Scripts here
	};

	class GameLoop
	{
	public:
		void run();

		void addNewEntity(Entity entity);
		void destroyEntity(Entity& entity);

		[[nodiscard]] bool isRunning() const { return m_isRunning; }

	private:
		bool m_isRunning{};

		scripting::ScriptHost m_scriptHost;
		std::vector<Entity>   m_entities;
	};
} // namespace engine