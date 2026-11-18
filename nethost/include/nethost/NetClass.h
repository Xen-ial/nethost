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
	/**
	 * @brief Container for managed C# classes, simplifies interactions with function invocation, and getting managed function delegates.
	 */
	class NetClass
	{
	public:
		/**
		 * @brief Constructs a managed net class container.
		 * @param app Target host app context
		 * @param libName Library name
		 * @param nameSpace Class namespace
		 * @param className Class name
		 */
		NetClass(BorrowedRef<NetHostApp> app, std::string libName, std::string nameSpace, std::string className)
		    : m_nethostApp(app), m_libName(std::move(libName)), m_nameSpace(std::move(nameSpace)), m_className(std::move(className))
		{
		}

		/**
		 * @brief Get the managed delegate function
		 * @param methodName Target function name
		 * @return Func Function delegate
		 */
		Func getFunc(const std::string& methodName);

		/**
		 * @brief Get the managed delegate function with a return type
		 * @tparam T Managed function delegate type
		 * @param methodName Target function name
		 * @return T Returns managed function delegate type
		 */
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

		/**
		 * @brief Handles function invocation with auto type deduction, and argument forwarding
		 * @tparam T Delegate type
		 * @tparam TArgs Delegate args
		 * @param methodName Target method name
		 * @param args Method arguments
		 * @return decltype(auto) Method return value
		 */
		template <typename T, typename... TArgs>
		decltype(auto) invokeFunc(const std::string& methodName, TArgs... args)
		{
			T func           = getFunc<T>(methodName);
			using ReturnType = decltype(func(std::forward<TArgs>(args)...));

			if constexpr (std::is_void_v<ReturnType>)
			{
				func(std::forward<TArgs>(args)...);
				return;
			}
			else
			{
				ReturnType result = func(std::forward<TArgs>(args)...);
				return result;
			}
		}

		/**
		 * @brief Handles function invocation with auto type deduction, without arguments
		 * @tparam T Delegate type
		 * @param methodName Target method name
		 * @return decltype(auto) Method return value
		 */
		template <typename T>
		decltype(auto) invokeFunc(const std::string& methodName)
		{
			T func           = getFunc<T>(methodName);
			using ReturnType = decltype(func());

			if constexpr (std::is_void_v<ReturnType>)
			{
				func();
				return;
			}
			else
			{
				ReturnType result = func();
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