#pragma once
#include <nethost/NetHostApp.h>
#include <scripting/NativeBridge.h>

#include <string>
#include <optional>

namespace scripting
{
	class ScriptHost
	{
	public:
		ScriptHost(const ScriptHost&)            = delete;
		ScriptHost& operator=(const ScriptHost&) = delete;

		ScriptHost(ScriptHost&&)            = delete;
		ScriptHost& operator=(ScriptHost&&) = delete;

		ScriptHost();
		~ScriptHost();

		void loadAssembly(const std::string& path);
		void loadAssemblyRelative(const std::string& path);

		void createEntity(int entityId);
		void destroyEntity(int entityId);
		void printAllEntities();
		void updateScripts();

		void addScript(int entityId, std::string scriptName);

	private:
		nethost::NetHostApp         m_nethostApp;
		std::optional<NativeBridge> m_nativeBridge;

		bool init();
	};
} // namespace scripting