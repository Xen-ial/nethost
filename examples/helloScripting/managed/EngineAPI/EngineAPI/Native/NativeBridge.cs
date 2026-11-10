using System.Runtime.InteropServices;

namespace EngineAPI.Native;

[StructLayout(LayoutKind.Sequential)]
public struct NativeFuncPointers
{
	public IntPtr PTestCall;
}

public static class NativeBridge
{
	private static VoidCall<EmptyArgs> _testCall;

	public static int InitalizeHostCallbacks(NativeFuncPointers funcs)
	{
		_testCall = funcs.PTestCall;
		return 0;
	}

	public static void TestCall()
	{
		if (!_testCall.IsResolved())
		{
			Console.WriteLine("Native bridge not properly initialized, failed to call _testCall()");
			return;
		}

		_testCall.Invoke();
	}
}