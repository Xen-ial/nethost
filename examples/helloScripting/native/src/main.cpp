#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

#include <filesystem>
#include <print>
#include <optional>

using EmptyVoid    = void(NETHOST_DELEGATE_CALLTYPE*)();
using LoadAssembly = unsigned char(NETHOST_DELEGATE_CALLTYPE*)(const char*);

namespace
{
	class MyApp
	{
	public:
		MyApp(const MyApp&)            = delete;
		MyApp& operator=(const MyApp&) = delete;

		MyApp(MyApp&&)            = delete;
		MyApp& operator=(MyApp&&) = delete;

		MyApp()
		    : m_app("Default.runtimeconfig.json")
		{
			if (!init())
				throw std::runtime_error("MyApp failed to initialize");
		}

		~MyApp()
		{
			m_app.shutdown();
			std::println("Shutting down .net app domain");
		}

		void createScriptingDomain()
		{
			if (m_createScriptingDomain == nullptr || !m_app.isInititalized())
			{
				std::println("Failed to call createScriptingDomain did you forget to initialize?");
				return;
			}

			m_createScriptingDomain();
		}

		void destroyScriptingDomain()
		{
			if (m_destroyScriptingDomain == nullptr)
				return;

			m_destroyScriptingDomain();
		}

		void loadAssembly(const std::string& path)
		{
			if (m_loadAssembly == nullptr)
				return;

			m_loadAssembly(path.c_str());
		}

		void loadAssemblyRelative(const std::string& relativePath)
		{
			if (m_loadAssembly == nullptr)
				return;

			auto path = std::filesystem::absolute(relativePath);
			m_loadAssembly(path.c_str());
		}

	private:
		nethost::NetHostApp              m_app;
		std::optional<nethost::Assembly> m_nativeBridge;

		EmptyVoid m_createScriptingDomain  = nullptr;
		EmptyVoid m_destroyScriptingDomain = nullptr;

		LoadAssembly m_loadAssembly = nullptr;

		bool init()
		{
			if (!m_app.isInititalized())
				return false;

			m_nativeBridge.emplace(m_app, "NativeBridge.dll", "NativeBridge");
			return loadFunctions();
		}

		bool loadFunctions()
		{
			if (!m_nativeBridge.has_value())
				return false;

			m_createScriptingDomain = m_nativeBridge->getFunc<EmptyVoid>(
			    "CreateScriptingDomain", "NativeBridge", "Entry");

			if (m_createScriptingDomain == nullptr)
			{
				std::println("Failed to resolve CreateScriptingDomain");
				return false;
			}

			m_destroyScriptingDomain = m_nativeBridge->getFunc<EmptyVoid>(
			    "DestroyScriptingDomain", "NativeBridge", "Entry");

			if (m_destroyScriptingDomain == nullptr)
			{
				std::println("Failed to resolve DestroyScriptingDomain");
				return false;
			}

			m_loadAssembly = m_nativeBridge->getFunc<LoadAssembly>(
			    "LoadAssembly", "NativeBridge", "Entry");

			if (m_loadAssembly == nullptr)
			{
				std::println("Failed to load assembly ptr");
				return false;
			}

			return true;
		}
	};
} // namespace

int main(int argc, const char* argv[])
{
	try
	{
		MyApp myApp;
		myApp.createScriptingDomain();
		myApp.loadAssemblyRelative("ExampleScripts.dll");
		myApp.destroyScriptingDomain();
	}
	catch (const std::exception except)
	{
		std::println("Exception thrown: {}", except.what());
	}

	return 0;
}