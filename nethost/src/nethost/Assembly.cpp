#include <nethost/Assembly.h>

#include <print>
#include <format>

namespace nethost
{
	Assembly::Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName)
	    : m_nethost(nethostApp), m_libName(std::move(libName))
	{
		auto netHost      = m_nethost.get();
		auto loadAssembly = netHost.getLoadAssembly();

		int result = loadAssembly(assemblyPath.c_str(),
		    nullptr, nullptr);

		if (result == 0)
		{
			std::println("failed to load assembly: {}", assemblyPath);
			return;
		}
	}

	Func Assembly::getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass)
	{
		auto netHost = m_nethost.get();
		auto func    = netHost.getFunc(methodName, nameSpace, targetClass, m_libName);

		if (func == nullptr)
			return nullptr;

		return func;
	}
} // namespace nethost