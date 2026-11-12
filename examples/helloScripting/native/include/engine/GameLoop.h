#pragma once
#include <scripting/ScriptHost.h>

#include <string>
#include <unordered_set>

namespace engine
{
	struct Vec3
	{
		float x;
		float y;
		float z;
	};

	struct Transform
	{
		Vec3 position;
		Vec3 scale;
		Vec3 rotation;
	};

	class Entity
	{
	public:
		Entity(int eId) : m_eId(eId) {}

		void addNetComponent(const std::string& compName);
		void addNetScript(const std::string& scrName);

		void removeNetComponent(const std::string& compName);
		void removeNetScript(const std::string& scrName);

		[[nodiscard]] int entId() const { return m_eId; }

	private:
		int m_eId;

		std::unordered_set<std::string> m_netComponents;
		std::unordered_set<std::string> m_netScripts;

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

		std::vector<Entity> m_entities;
	};
} // namespace engine