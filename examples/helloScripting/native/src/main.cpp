#include <engine/GameLoop.h>

#include <nethost/NetHostApp.h>
#include <nethost/Assembly.h>

#include <print>

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