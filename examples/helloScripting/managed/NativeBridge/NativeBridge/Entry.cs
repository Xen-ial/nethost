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
		_scriptingDomain = new AssemblyLoadContext("ExampleEngineDomain", isCollectible: true);
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
	public static int Initialize(IntPtr nativeFuncPtrs)
	{
		NativeFuncPointers funcPtrs = Marshal.PtrToStructure<NativeFuncPointers>(nativeFuncPtrs);
		return EngineAPI.Native.NativeBridge.InitalizeHostCallbacks(funcPtrs);
	}

	[UnmanagedCallersOnly]
	public static void CreateEntity(int id)
	{
		EngineAPI.Native.NativeBridge.CreateEntity(id);
	}

	[UnmanagedCallersOnly]
	public static void DestroyEntity(int id)
	{
		EngineAPI.Native.NativeBridge.DestroyEntity(id);
	}

	[UnmanagedCallersOnly]
	public static void PrintAllEntities()
	{
		EngineAPI.Native.NativeBridge.PrintAllEntities();
	}

	[UnmanagedCallersOnly]
	public static void UpdateScripts()
	{
		EngineAPI.Native.NativeBridge.UpdateScripts();
	}

	[UnmanagedCallersOnly]
	public static void AddScript(int entityId, IntPtr scriptName)
	{
		var entity = EngineAPI.Native.NativeBridge.GetEntity(entityId);
		if (entity == null)
		{
			Console.WriteLine("Entity is null");
			return;
		}

		if (_scriptingDomain == null)
		{
			Console.WriteLine("Scripting Domain is not created can not resolve scripts.");
			return;
		}

		EngineAPI.Native.NativeBridge.AddScript(scriptName, entity, [.. _scriptingDomain.Assemblies]);
	}
}