using EngineAPI.Engine.Scripting;

namespace ExampleScripts;

public class HelloWorld : Script
{
	public override void Update(float deltaTime)
	{
		Console.WriteLine("Hello World, Update()");
	}

	public override void OnDraw(float deltaTime)
	{
		Console.WriteLine("Hello World, OnDraw()");
	}
}