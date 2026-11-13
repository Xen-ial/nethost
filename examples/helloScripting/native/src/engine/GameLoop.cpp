#include <engine/GameLoop.h>

namespace engine
{
	void Entity::addNetComponent(const std::string& compName)
	{
		if (m_netComponents.contains(compName))
			return;

		m_netComponents.emplace(compName);
	}

	void Entity::addNetScript(const std::string& scrName)
	{
		if (m_netScripts.contains(scrName))
			return;

		m_netScripts.emplace(scrName);
	}

	void Entity::removeNetComponent(const std::string& compName)
	{
		if (m_netComponents.contains(compName))
			m_netComponents.erase(compName);
	}

	void Entity::removeNetScript(const std::string& scrName)
	{
		if (m_netScripts.contains(scrName))
			m_netScripts.erase(scrName);
	}

	void GameLoop::run()
	{
		m_scriptHost.loadAssemblyRelative("ExampleScripts.dll");

		Entity entity1(0);
		entity1.addNetScript("HelloWorld");

		addNewEntity(entity1);

		m_scriptHost.printAllEntities();

		m_isRunning = true;
		while (isRunning())
		{
			m_scriptHost.updateScripts();
		}
	}

	void GameLoop::addNewEntity(Entity entity)
	{
		m_scriptHost.createEntity(entity.entId());

		for (const auto& scripts : entity.getNetScripts())
			m_scriptHost.addScript(entity.entId(), scripts);

		m_entities.push_back(std::move(entity));
	}

	void GameLoop::destroyEntity(Entity& entity)
	{
		m_scriptHost.destroyEntity(entity.entId());

		int index{};
		for (int i = 0; i < m_entities.size(); i++)
		{
			auto ent = m_entities[i];
			if (ent.entId() != entity.entId())
				continue;

			index = i;
			break;
		}

		m_entities.erase(m_entities.begin() + index);
	}
} // namespace engine