#include <sharphost/Host.h>

#include <print>
#include <filesystem>

int main()
{
	sharphost::Host host("SharpHost.dll");

	auto testContext = host.createAssemblyContext("TestContext");
	testContext.loadAssembly("");

	return 0;
}