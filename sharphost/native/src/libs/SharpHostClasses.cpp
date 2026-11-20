#include <sharphost/libs/SharpHostClasses.h>

#include <nethost/NetClass.h>
#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

namespace sharphost::classes
{
	ManagedHostClass::ManagedHostClass(nethost::BorrowedRef<nethost::Assembly> sharpHostAssembly)
	    : m_sharpHostAssembly(sharpHostAssembly),
	      nethost::NetClass(sharpHostAssembly.get().getNetClass("SharpHost", "ManagedHost"))
	{
	}

	void ManagedHostClass::createAssemblyLoadContext(const std::string& contextName)
	{
		using CreateAssemblyLoadContextFunc = void(NETHOST_DELEGATE_CALLTYPE*)(const char* contextName);
		invokeFunc<CreateAssemblyLoadContextFunc>("CreateAssemblyLoadContext", contextName.c_str());
	}

	void ManagedHostClass::unloadAndDestroyAssemblyContext(const std::string& contextName)
	{
		using UnloadAndDestroyAssemblyContextFunc = void(NETHOST_DELEGATE_CALLTYPE*)(const char* contextName);
		invokeFunc<UnloadAndDestroyAssemblyContextFunc>("UnloadAndDestroyAssemblyContext", contextName.c_str());
	}

	void ManagedHostClass::rebuildMaps()
	{
		using RebuildMapsFunc = void(NETHOST_DELEGATE_CALLTYPE*)();
		invokeFunc<RebuildMapsFunc>("RebuildMaps");
	}

	void ManagedHostClass::loadAssemblyFromPath(const std::string& contextName, const std::string& path)
	{
		using LoadAssemblyFromPathFunc = void(NETHOST_DELEGATE_CALLTYPE*)(const char* contextName, const char* targetPath);
		invokeFunc<LoadAssemblyFromPathFunc>("LoadAssemblyFromPath", contextName.c_str(), path.c_str());
	}

	void ManagedHostClass::loadAssemblyFromBytes(const std::string& contextName, const std::vector<std::byte>& assemblyBytes)
	{
		using LoadAssemblyFromBytesFunc = void(NETHOST_DELEGATE_CALLTYPE*)(const char* contextName, const std::byte* assemblyBytes, int assemblyLength);
		invokeFunc<LoadAssemblyFromBytesFunc>("LoadAssemblyFromBytes", contextName.c_str(), assemblyBytes.data(), static_cast<int>(assemblyBytes.size()));
	}

	void ManagedHostClass::printClasses()
	{
		using PrintClassFunc = void(NETHOST_DELEGATE_CALLTYPE*)();
		invokeFunc<PrintClassFunc>("DisplayFoundClasses");
	}
} // namespace sharphost::classes