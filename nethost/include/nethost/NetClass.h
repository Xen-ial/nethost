#pragma once
#include <nethost/NetHostApp.h>
#include <nethost/Utils.h>

#include <string>
#include <print>

namespace nethost
{
	class NetClass
	{
	public:
		NetClass(BorrowedRef<NetHostApp> app, std::string libName, std::string nameSpace, std::string className)
		    : m_nethostApp(app), m_libName(std::move(libName)), m_nameSpace(std::move(nameSpace)), m_className(std::move(className))
		{
		}

		Func getFunc(const std::string& methodName);

		template <typename T>
		T getFunc(const std::string& methodName)
		{
			auto& host = m_nethostApp.get();

			if (!host.isInititalized())
			{
				std::println("Failed to get func for unloaded assembly: {}", m_libName);
				return nullptr;
			}

			T delegate = nullptr;
			host.getFuncDelegate(reinterpret_cast<void**>(&delegate), methodName, m_nameSpace, m_className, m_libName);

			return delegate;
		}

	private:
		BorrowedRef<NetHostApp> m_nethostApp;
		std::string             m_libName;
		std::string             m_nameSpace;
		std::string             m_className;
	};
} // namespace nethost