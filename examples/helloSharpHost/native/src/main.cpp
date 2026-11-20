#include <sharphost/Host.h>

#include <print>
#include <filesystem>

// TODO: Get all data from C# to C++ 

int main()
{
	sharphost::Host host("SharpHost.dll");

	auto testContext = host.createAssemblyContext("TestContext");
	testContext.loadAssembly("Test.dll");

	auto metadata = testContext.getMetadata();
	std::println("Assembly-FullName: {}", metadata.findAssembly("Test").metadata.fullName);

	return 0;
}