#include <sharphost/libs/SharpHostClasses.h>

#include <nethost/NetClass.h>
#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

namespace sharphost::classes
{
	ManagedHostClass::ManagedHostClass(nethost::BorrowedRef<nethost::Assembly> sharpHostAssembly)
	    : m_sharpHostAssembly(sharpHostAssembly),
	      nethost::NetClass(sharpHostAssembly.get().getNetClass("SharpHost", "ManagedHost"))
	{
	}
} // namespace sharphost::classes