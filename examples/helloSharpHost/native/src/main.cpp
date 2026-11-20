#include <sharphost/Host.h>

#include <print>
#include <filesystem>

int main()
{
	sharphost::Host host("SharpHost.dll");

	auto sharpHost   = host.getSharpHost();
	auto managedHost = sharpHost.getManagedHost();

	return 0;
}