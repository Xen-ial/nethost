using EngineAPI.Native;

namespace EngineAPI.Engine;

public class Engine
{
	public Engine()
	{
	}

	public void Test()
	{
		NativeBridge.TestCall();
	}
}