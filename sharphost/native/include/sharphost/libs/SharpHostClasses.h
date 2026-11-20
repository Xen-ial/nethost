#pragma once
#include <nethost/Assembly.h>
#include <nethost/NetClass.h>
#include <nethost/Utils.h>

#include <string>
#include <vector>
#include <cstddef>

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

		void createAssemblyLoadContext(const std::string& contextName);
		void unloadAndDestroyAssemblyContext(const std::string& contextName);
		void rebuildMaps();

		void loadAssemblyFromPath(const std::string& contextName, const std::string& path);
		void loadAssemblyFromBytes(const std::string& contextName, const std::vector<std::byte>& assemblyBytes);

		void printClasses();

	private:
		nethost::BorrowedRef<nethost::Assembly> m_sharpHostAssembly;

		[[nodiscard]] bool hasAssemblyLoaded() const { return m_sharpHostAssembly.get().hasAssemblyLoaded(); }
	};
} // namespace sharphost::classes