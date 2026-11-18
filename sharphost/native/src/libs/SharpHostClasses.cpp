#include <sharphost/libs/SharpHostClasses.h>

#include <nethost/NetClass.h>
#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

namespace sharphost::classes
{
	ManagedHostClass::ManagedHostClass(nethost::BorrowedRef<nethost::Assembly> sharpHostAssembly)
	    : m_sharpHostAssembly(sharpHostAssembly),
	      nethost::NetClass(sharpHostAssembly.get().getNetHostApp(), sharpHostAssembly.get().getLibName(),
	          "SharpHost", "ManagedHost")
	{
		if (!loadFuncs())
			nethost::err::logln("Failed to load ManagedHost functions", nethost::err::StatusCode::FAILURE);
	}
} // namespace sharphost::classes