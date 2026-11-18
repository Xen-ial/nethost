#pragma once
#include <nethost/Assembly.h>
#include <nethost/NetClass.h>
#include <nethost/Utils.h>

namespace sharphost::classes
{
	/**
	 * @brief Managed Host contains all the main functionality for interacting with other C# assemblies
	 * Simplifies interactions with functions, and getting reflection information.
	 */
	class ManagedHostClass : public nethost::NetClass
	{
	public:
		ManagedHostClass(nethost::BorrowedRef<nethost::Assembly> sharpHostAssembly);

	private:
		nethost::BorrowedRef<nethost::Assembly> m_sharpHostAssembly;

		[[nodiscard]] bool hasAssemblyLoaded() const { return m_sharpHostAssembly.get().hasAssemblyLoaded(); }
	};
} // namespace sharphost::classes