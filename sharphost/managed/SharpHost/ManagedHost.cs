using System.Runtime.InteropServices;

namespace SharpHost;

public class ManagedHost
{
	[UnmanagedCallersOnly]
	public static void TestCall()
	{
		Console.WriteLine("Test Call");
	}
}