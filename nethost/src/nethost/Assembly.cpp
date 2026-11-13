#include "nethost/ErrorCodes.h"
#include <nethost/Assembly.h>
#include <nethost/NetClass.h>

#include <nethost/Log.h>

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
			err::logln(std::format("failed to load assembly {}", assemblyPath), err::StatusCode::CORE_CLR_RESOLVE_FAILURE);
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
			err::logln(std::format("failed to load assembly: {}", libName), err::StatusCode::CORE_CLR_RESOLVE_FAILURE);
			return;
		}

		m_hasLoaded = true;
	}

	Func Assembly::getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass)
	{
		if (!m_hasLoaded)
		{
			err::logln(std::format("Failed to get func for unloaded assembly: {}", m_libName), err::StatusCode::CORE_CLR_RESOLVE_FAILURE);
			return nullptr;
		}

		auto& netHost = m_nethost.get();
		auto func    = netHost.getFunc(methodName, nameSpace, targetClass, m_libName);
		return func;
	}

	NetClass Assembly::getNetClass(std::string nameSpace, std::string className)
	{
		return std::move(NetClass(m_nethost, m_libName, std::move(nameSpace), std::move(className)));
	}
} // namespace nethost