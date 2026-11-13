#include <nethost/NetClass.h>

namespace nethost
{
	Func NetClass::getFunc(const std::string& methodName)
	{
		auto& nethost = m_nethostApp.get();
		auto func    = nethost.getFunc(methodName, m_nameSpace, m_className, m_libName);
		return func;
	}
} // namespace nethost