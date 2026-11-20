#pragma once
#include <sharphost/libs/SharpHostLib.h>
#include <nethost/Utils.h>

#include <string>
#include <vector>
#include <cstddef>

namespace sharphost
{
	class AssemblyContext
	{
	public:
		AssemblyContext(const AssemblyContext&)            = default;
		AssemblyContext& operator=(const AssemblyContext&) = default;

		AssemblyContext(AssemblyContext&&)            = default;
		AssemblyContext& operator=(AssemblyContext&&) = default;

		AssemblyContext(nethost::BorrowedRef<SharpHostLib> sharpHostLib, std::string contextName);
		~AssemblyContext();

		void loadAssembly(const std::string& path);
		void loadAssembly(const std::vector<std::byte>& assemblyBytes);

		void rebuildReflectionMap();
        void unload();
		
	private:
		nethost::BorrowedRef<SharpHostLib> m_sharpHostLib;

		std::string m_contextName;
	};
} // namespace sharphost