using System.Runtime.InteropServices;
using System.Runtime.Loader;
using EngineAPI.Native;

namespace NativeBridge;

public static class Entry
{
	private static AssemblyLoadContext? _scriptingDomain;

	[UnmanagedCallersOnly]
	public static void CreateScriptingDomain()
	{
		Console.WriteLine("Created Domain");
		_scriptingDomain = new AssemblyLoadContext("ScriptingDomain", isCollectible: true);
	}

	[UnmanagedCallersOnly]
	public static void DestroyScriptingDomain()
	{
		Console.WriteLine("Unloaded Domain");
		_scriptingDomain?.Unload();
	}

	[UnmanagedCallersOnly]
	public static unsafe byte LoadAssembly(byte* pathBytes)
	{
		Console.WriteLine("Loading Assembly");

		try
		{
			var path = Marshal.PtrToStringUTF8((IntPtr)pathBytes);
			if (_scriptingDomain == null || path == null) return 0;

			_ = _scriptingDomain.LoadFromAssemblyPath(path);
		}
		catch (Exception e)
		{
			Console.WriteLine($"Failed to load assembly {e.Message}");
			return 0;
		}

		return 1;
	}

	[UnmanagedCallersOnly]
	public static void Initialize(IntPtr testCallPtr)
	{
		EngineAPI.Native.NativeBridge.InitalizeHostCallbacks(testCallPtr);
	}
}