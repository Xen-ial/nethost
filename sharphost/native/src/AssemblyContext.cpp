#include <sharphost/AssemblyContext.h>

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
		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.unloadAndDestroyAssemblyContext(m_contextName);
		managedHost.rebuildMaps();
	}

	void AssemblyContext::rebuildReflectionMap()
	{
	}

	void AssemblyContext::loadAssembly(const std::string& path)
	{
		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.loadAssemblyFromPath(m_contextName, path);
		managedHost.rebuildMaps();
	}

	void AssemblyContext::loadAssembly(const std::vector<std::byte>& assemblyBytes)
	{
		auto managedHost = m_sharpHostLib.get().getManagedHost();
		managedHost.loadAssemblyFromBytes(m_contextName, assemblyBytes);
		managedHost.rebuildMaps();
	}
} // namespace sharphost