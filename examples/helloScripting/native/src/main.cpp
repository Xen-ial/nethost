#include <engine/GameLoop.h>

#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

#include <print>

// TODO: Implemented removeScript, addComponent, removeComponent
// TODO: Rewrite documentation
// TODO: Add a few simulated engine api function examples
// TODO: Link ECS system with Scripting system
// TODO: Transform syncing example

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