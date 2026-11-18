#pragma once
#include <sharphost/libs/SharpHostClasses.h>
#include <nethost/Assembly.h>

#include <string>

namespace sharphost
{
	class SharpHostLib : public nethost::Assembly
	{
	public:
		SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app, const std::string& path);
		SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app);

		[[nodiscard]] classes::ManagedHostClass getManagedHost() const { return m_managedHost; }

	private:
		nethost::BorrowedRef<nethost::NetHostApp> m_appHost;
		classes::ManagedHostClass                 m_managedHost;

		static std::vector<std::byte> getSharpHostLibBytes();
	};
} // namespace sharphost