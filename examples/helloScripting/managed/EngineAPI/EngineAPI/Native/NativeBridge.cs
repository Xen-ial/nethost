namespace EngineAPI.Native;

public static class NativeBridge
{
	private static unsafe delegate* unmanaged[Cdecl]<void> _testCall;

	public static unsafe int InitalizeHostCallbacks(IntPtr testCallPtr)
	{
		if (testCallPtr == IntPtr.Zero) return -1;
		_testCall = (delegate* unmanaged[Cdecl]<void>)testCallPtr;
		return 0;
	}

	public static unsafe void TestCall()
	{
		if (_testCall == null) return;
		_testCall();
	}
}