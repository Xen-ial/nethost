#include <sharphost/AssemblyContext.h>
#include <sharphost/Host.h>

#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

#include <string>

namespace sharphost
{
	Host::Host(const std::string& sharphostAssemPath)
	{
		if (!m_appHost.isInititalized())
		{
			nethost::err::logln("Sharp host failed to initialize!", nethost::err::StatusCode::HOST_INVALID_STATE);
			return;
		}

		m_sharpHostLib.emplace(m_appHost, sharphostAssemPath);
		if (!m_sharpHostLib.has_value()) return;
	}

	Host::Host()
	{
		if (!m_appHost.isInititalized())
		{
			nethost::err::logln("Sharp host failed to initialize!", nethost::err::StatusCode::HOST_INVALID_STATE);
			return;
		}

		m_sharpHostLib.emplace(m_appHost);
		if (!m_sharpHostLib.has_value()) return;
	}

	AssemblyContext Host::createAssemblyContext(std::string contextName)
	{
		AssemblyContext context(m_sharpHostLib.value(), std::move(contextName));
		return std::move(context);
	}
} // namespace sharphost