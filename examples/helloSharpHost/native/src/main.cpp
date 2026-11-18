#include <sharphost/Host.h>

int main()
{
	sharphost::Host host("SharpHost.dll");

	auto sharpHost = host.getSharpHost();

	auto managedHost = sharpHost.getManagedHost();
	managedHost.testCall();

	return 0;
}