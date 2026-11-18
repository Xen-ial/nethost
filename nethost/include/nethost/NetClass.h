#pragma once
#include <nethost/NetHostApp.h>
#include <nethost/Utils.h>
#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

#include <string>
#include <format>
#include <type_traits>

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
				err::logln((std::format("failed to get func for unloaded assembly {}", m_libName)), err::StatusCode::CORE_CLR_RESOLVE_FAILURE);
				return nullptr;
			}

			T delegate = nullptr;
			host.getFuncDelegate(reinterpret_cast<void**>(&delegate), methodName, m_nameSpace, m_className, m_libName);

			return delegate;
		}

		template <typename T, typename... TArgs>
		decltype(auto) invokeFunc(const std::string& methodName, TArgs... args)
		{
			T func         = getFunc<T>(methodName);
			using FuncType = decltype(func(std::forward<TArgs>(args)...));

			if constexpr (std::is_void_v<T>)
			{
				func(std::forward<TArgs>(args)...);
				return;
			}
			else
			{
				FuncType result = func(std::forward<TArgs>(args)...);
				return result;
			}
		}

		template <typename T>
		decltype(auto) invokeFunc(const std::string& methodName)
		{
			T func         = getFunc<T>(methodName);
			using FuncType = decltype(func());

			if constexpr (std::is_void_v<FuncType>)
			{
				func();
				return;
			}
			else
			{
				FuncType result = func();
				return result;
			}
		}

	private:
		BorrowedRef<NetHostApp> m_nethostApp;
		std::string             m_libName;
		std::string             m_nameSpace;
		std::string             m_className;
	};
} // namespace nethost