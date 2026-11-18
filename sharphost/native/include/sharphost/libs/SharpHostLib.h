#pragma once
#include <sharphost/libs/SharpHostClasses.h>
#include <nethost/Assembly.h>

#include <string>

namespace sharphost
{
	/**
	 * @brief SharpHost bootstrap library, containing all managed host interactions
	 */
	class SharpHostLib : public nethost::Assembly
	{
	public:
		/**
		 * @brief Loads the nethost assembly, and initializes access to all classes
		 * @param app Target app context
		 * @param path Target managed DLL path
		 */
		SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app, const std::string& path);

		/**
		 * @brief Loads the nethost assembly from memory, and initializes access to all classes
		 * @param app Target app context
		 */
		SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app);

		/**
		 * @brief Gets the Managed Host class from SharpHostLib
		 * @return classes::ManagedHostClass Returns managed host class
		 */
		[[nodiscard]] classes::ManagedHostClass getManagedHost() const { return m_managedHost; }

	private:
		nethost::BorrowedRef<nethost::NetHostApp> m_appHost;
		classes::ManagedHostClass                 m_managedHost;

		/**
		 * @brief Get the Sharp Host Library Bytes
		 * @return std::vector<std::byte> Returns managed sharp host library bytes
		 */
		static std::vector<std::byte> getSharpHostLibBytes();
	};
} // namespace sharphost