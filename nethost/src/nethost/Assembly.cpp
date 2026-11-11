#include <nethost/Assembly.h>

#include <print>
#include <format>

namespace nethost
{
	Assembly::Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName)
	    : m_nethost(nethostApp), m_libName(std::move(libName))
	{
		auto netHost = m_nethost.get();
		bool result  = netHost.loadAssembly(assemblyPath.c_str());

		if (!result)
		{
			std::println("failed to load assembly: {}", assemblyPath);
			return;
		}

		m_hasLoaded = true;
	}

	Assembly::Assembly(BorrowedRef<NetHostApp> nethostApp, const std::vector<std::byte>& assemblyBytes, std::string libName)
	    : m_nethost(nethostApp), m_libName(std::move(libName))
	{
		auto netHost = m_nethost.get();
		auto result  = netHost.loadAssembly(assemblyBytes);

		if (!result)
		{
			std::println("failed to load assembly: {}", libName);
			return;
		}

		m_hasLoaded = true;
	}

	Func Assembly::getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass)
	{
		if (!m_hasLoaded)
		{
			std::println("Failed to get func for unloaded assembly: {}", m_libName);
			return nullptr;
		}

		auto netHost = m_nethost.get();
		auto func    = netHost.getFunc(methodName, nameSpace, targetClass, m_libName);

		if (func == nullptr)
			return nullptr;

		return func;
	}
} // namespace nethost