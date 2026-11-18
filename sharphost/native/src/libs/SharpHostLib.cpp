#include <sharphost/libs/SharpHostLib.h>

namespace sharphost
{
	SharpHostLib::SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app, const std::string& path)
	    : m_appHost(app), nethost::Assembly(app, path, "SharpHost"),
	      m_managedHost(*this)
	{
		if (!hasAssemblyLoaded())
			nethost::err::logln("Sharp host bootstrap library failed to load", nethost::err::StatusCode::CORE_HOST_LIB_LOAD_FAILURE);
	}

	SharpHostLib::SharpHostLib(nethost::BorrowedRef<nethost::NetHostApp> app)
	    : m_appHost(app), nethost::Assembly(app, getSharpHostLibBytes(), "SharpHost"),
	      m_managedHost(*this)
	{
		if (!hasAssemblyLoaded())
			nethost::err::logln("Sharp host bootstrap library failed to load", nethost::err::StatusCode::CORE_HOST_LIB_LOAD_FAILURE);
	}

	// TODO: Load assembly from in memory resource bytes
	std::vector<std::byte> SharpHostLib::getSharpHostLibBytes()
	{
		return {};
	}
} // namespace sharphost