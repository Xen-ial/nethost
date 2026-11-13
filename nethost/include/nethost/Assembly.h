#pragma once
#include "nethost/ErrorCodes.h"
#include <nethost/NetHostApp.h>
#include <nethost/NetClass.h>
#include <nethost/Utils.h>

#include <nethost/Log.h>

#include <cstddef>
#include <vector>
#include <string>
#include <format>

namespace nethost
{
	class Assembly
	{
	public:
		Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName);
		Assembly(BorrowedRef<NetHostApp> nethostApp, const std::vector<std::byte>& assemblyBytes, std::string libName);

		Func getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass);

		template <typename T>
		T getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass)
		{
			if (!m_hasLoaded)
			{
				err::logln(std::format("Failed to get func for unloaded assembly {}", m_libName), err::StatusCode::EMPTY);
				return nullptr;
			}

			auto& host = m_nethost.get();

			T delegate = nullptr;
			host.getFuncDelegate(reinterpret_cast<void**>(&delegate), methodName, nameSpace, targetClass, m_libName);

			return delegate;
		}

		NetClass getNetClass(std::string nameSpace, std::string className);

		[[nodiscard]] bool        hasAssemblyLoaded() const { return m_hasLoaded; }
		[[nodiscard]] std::string getLibName() const { return m_libName; }

	private:
		BorrowedRef<NetHostApp> m_nethost;

		bool m_hasLoaded{};

		std::string m_libName;
	};

} // namespace nethost