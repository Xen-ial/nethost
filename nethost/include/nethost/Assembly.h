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
	/**
	 * @brief C# Assembly / Class Library wrapper. Simplifies Host FXR interactions with function calls.
	 */
	class Assembly
	{
	public:
		/**
		 * @brief Creates and loads a new assembly via the assembly's path on disk
		 * @param nethostApp Target host context
		 * @param assemblyPath Target .NET assembly
		 * @param libName Target library's name
		 */
		Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName);

		/**
		 * @brief Creates and loads a new assembly via the assembly's bytes from memory
		 * @param nethostApp Target host context
		 * @param assemblyBytes Target .NET assembly bytes
		 * @param libName Target library name
		 */
		Assembly(BorrowedRef<NetHostApp> nethostApp, const std::vector<std::byte>& assemblyBytes, std::string libName);

		/**
		 * @brief Get assembly function delegate pointer
		 * @param methodName Target method name
		 * @param nameSpace Target class namespace
		 * @param targetClass Target class
		 * @return Func Function delegate
		 */
		Func getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass);

		/**
		 * @brief Get assembly function delegate pointer
		 * @tparam T Delegate type
		 * @param methodName Target method name
		 * @param nameSpace Target class namespace
		 * @param targetClass Target class
		 * @return T Function Delegate
		 */
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

		/**
		 * @brief Get C# class container
		 * @param nameSpace Target namespace
		 * @param className Target class
		 * @return NetClass C# class container
		 */
		NetClass getNetClass(std::string nameSpace, std::string className);

		/**
		 * @brief Check if this current assembly has successfully loaded
		 * @return true Successfully loaded
		 * @return false Failed to load
		 */
		[[nodiscard]] bool hasAssemblyLoaded() const { return m_hasLoaded; }

		/**
		 * @brief Get the current library name
		 * @return std::string Library name
		 */
		[[nodiscard]] std::string getLibName() const { return m_libName; }

		/**
		 * @brief Get the Net Host App
		 * @return BorrowedRef<NetHostApp> NetHost reference
		 */
		[[nodiscard]] BorrowedRef<NetHostApp> getNetHostApp() const { return m_nethost; }

	private:
		BorrowedRef<NetHostApp> m_nethost;

		bool m_hasLoaded{};

		std::string m_libName;
	};

} // namespace nethost