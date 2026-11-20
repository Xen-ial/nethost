#include <format>
#include <sharphost/AssemblyContext.h>
#include <nethost/Log.h>

#include <filesystem>

namespace sharphost
{
	AssemblyContext::AssemblyContext(nethost::BorrowedRef<SharpHostLib> sharpHostLib, std::string contextName)
	    : m_sharpHostLib(sharpHostLib), m_contextName(std::move(contextName))
	{
		auto managedHost = sharpHostLib.get().getManagedHost();
		managedHost.createAssemblyLoadContext(m_contextName);
		managedHost.rebuildMaps();
	}

	AssemblyContext::~AssemblyContext()
	{
		unload();
	}

	void AssemblyContext::unload()
	{
		if (m_contextName.empty())
			return;

		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.unloadAndDestroyAssemblyContext(m_contextName);
		managedHost.rebuildMaps();
		m_contextName.clear();
	}

	void AssemblyContext::rebuildReflectionMap()
	{
	}

	void AssemblyContext::loadAssembly(const std::string& path)
	{
		std::error_code errorCode{};
		auto            absPath = std::filesystem::canonical(path, errorCode);

		if (errorCode.value() != 0)
		{
			nethost::err::logln(std::format("LoadAssembly {}", errorCode.message()), nethost::err::StatusCode::APP_PATH_FIND_FAILURE);
			return;
		}

		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.loadAssemblyFromPath(m_contextName, absPath);
		managedHost.rebuildMaps();
	}

	void AssemblyContext::loadAssembly(const std::vector<std::byte>& assemblyBytes)
	{
		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.loadAssemblyFromBytes(m_contextName, assemblyBytes);
		managedHost.rebuildMaps();
	}
} // namespace sharphost