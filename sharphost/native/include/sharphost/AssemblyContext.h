#pragma once
#include <sharphost/libs/SharpHostLib.h>
#include <sharphost/ManagedTypes.h>
#include <nethost/Utils.h>

#include <string>
#include <vector>
#include <cstddef>

namespace sharphost
{
	class AssemblyContext
	{
	public:
		AssemblyContext(const AssemblyContext&)            = delete;
		AssemblyContext& operator=(const AssemblyContext&) = delete;

		AssemblyContext(AssemblyContext&& other) noexcept
		    : m_contextName(std::move(other.m_contextName)), m_sharpHostLib(other.m_sharpHostLib)
		{
			other.m_assemblyContextMetadata.resetMetadata();
			other.m_contextName.clear();
		}

		AssemblyContext& operator=(AssemblyContext&& other) noexcept
		{
			if (this == &other) return *this;
			unload();

			m_contextName  = std::move(other.m_contextName);
			m_sharpHostLib = other.m_sharpHostLib;

			other.m_contextName.clear();
			other.m_assemblyContextMetadata.resetMetadata();
			return *this;
		}

		AssemblyContext(nethost::BorrowedRef<SharpHostLib> sharpHostLib, std::string contextName);
		~AssemblyContext();

		void loadAssembly(const std::string& path);
		void loadAssembly(const std::vector<std::byte>& assemblyBytes);

		void rebuildReflectionMap();
		void unload();

		[[nodiscard]] AssemblyContextMetadata getMetadata() const { return m_assemblyContextMetadata; }

	private:
		nethost::BorrowedRef<SharpHostLib> m_sharpHostLib;

		AssemblyContextMetadata m_assemblyContextMetadata;

		std::string m_contextName;
	};
} // namespace sharphost