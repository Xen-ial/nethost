#pragma once
#include <nethost/NetHostApp.h>
#include <sharphost/libs/SharpHostLib.h>

#include <sharphost/AssemblyContext.h>

#include <string>
#include <optional>

namespace sharphost
{
	class Host
	{
	public:
		Host(const std::string& sharpHostAssemPath);
		Host();

		AssemblyContext createAssemblyContext(std::string contextName);

		[[nodiscard]] SharpHostLib getSharpHost() const { return m_sharpHostLib.value(); }

	private:
		nethost::NetHostApp m_appHost;

		std::optional<SharpHostLib> m_sharpHostLib;
	};
} // namespace sharphost