#pragma once
#include <nethost/NetHostApp.h>
#include <nethost/Utils.h>
#include <string>

namespace nethost
{
	class Assembly
	{
	public:
		Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName);

		Func getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass);

		template <typename T>
		T getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass)
		{
			auto host = m_nethost.get();

			T delegate = nullptr;
			host.getFuncDelegate(reinterpret_cast<void**>(&delegate), methodName, nameSpace, targetClass, m_libName);

			return delegate;
		}

	private:
		BorrowedRef<NetHostApp> m_nethost;

		std::string m_libName;
	};
} // namespace nethost