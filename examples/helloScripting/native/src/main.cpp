#include <engine/GameLoop.h>

#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

#include <print>

// TODO: Create Engine/Game Loop (Simulated)
// TODO: Create actual Engine API examples
// TODO: Create Entity's with attached script references, entities are C++ owned
// TODO: Create Update/OnGUI/Resize/etc events for the scripting interface to consume
// TODO: Link ECS system with Scripting system

int main(int argc, const char* argv[])
{
	try
	{
		engine::GameLoop game;
		game.run();
	}
	catch (const std::exception except)
	{
		std::println("Exception thrown: {}", except.what());
	}

	return 0;
}