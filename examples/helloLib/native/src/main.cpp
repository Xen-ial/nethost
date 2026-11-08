#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

#include <print>

int main(int argc, const char* argv[])
{
	nethost::NetHostApp helloWorldApp("Default.runtimeconfig.json");
	if (!helloWorldApp.isInititalized())
		return 1;

	nethost::Assembly dotnetLib(helloWorldApp, "DotNetLib.dll", "DotNetLib");

	using MainEntryFn     = void(NETHOST_DELEGATE_CALLTYPE*)();
	MainEntryFn mainEntry = dotnetLib.getFunc<MainEntryFn>("Main", "DotNetLib", "Lib");

	if (mainEntry == nullptr)
	{
		std::println("Hello failed to be resolved");
		return 1;
	}

	using IsWaitingFn     = unsigned char(NETHOST_DELEGATE_CALLTYPE*)();
	IsWaitingFn isWaiting = dotnetLib.getFunc<IsWaitingFn>("IsWaiting", "DotNetLib", "Lib");

	if (isWaiting == nullptr)
	{
		std::println(("failed to resolve isWaiting"));
		return 1;
	}

	auto isWaitingValue = isWaiting();
	std::println("IsWaiting: {}", isWaitingValue);

	mainEntry();

	isWaitingValue = isWaiting();
	std::println("IsWaiting: {}", isWaitingValue);

	helloWorldApp.shutdown();
	return 0;
}