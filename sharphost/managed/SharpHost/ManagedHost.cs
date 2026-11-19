using System.Runtime.InteropServices;
using SharpHost.Assembly;
using SharpHost.Helpers;

namespace SharpHost;

public class ManagedHost
{
	private static readonly AssemblyContext AssemblyContext = new();

	[UnmanagedCallersOnly]
	public static void CreateAssemblyLoadContext(IntPtr assemblyLoadContextNameStrPtr)
	{
		var assemblyLoadContextName = Marshal.PtrToStringUTF8(assemblyLoadContextNameStrPtr);
		if (string.IsNullOrEmpty(assemblyLoadContextName))
		{
			ArgumentException.ThrowIfNullOrEmpty(assemblyLoadContextName);
			return;
		}

		AssemblyContext.CreateAssemblyLoadContext(assemblyLoadContextName);
	}

	[UnmanagedCallersOnly]
	public static void UnloadAndDestroyAssemblyContext(IntPtr assemblyContextNameStrPtr)
	{
		var assemblyContextName = Marshal.PtrToStringUTF8(assemblyContextNameStrPtr);
		if (string.IsNullOrEmpty(assemblyContextName))
		{
			ArgumentException.ThrowIfNullOrEmpty(assemblyContextName);
			return;
		}

		var loadContext = AssemblyContext.GetContext(assemblyContextName);
		if (loadContext == null)
		{
			ArgumentNullException.ThrowIfNull(loadContext);
			return;
		}

		AssemblyContext.UnloadAndDestroyAssemblyContext(assemblyContextName);
	}

	[UnmanagedCallersOnly]
	public static void LoadAssemblyFromPath(IntPtr assemblyContextNameStrPtr, IntPtr pathStrPtr)
	{
		var assemblyContextName = Marshal.PtrToStringUTF8(assemblyContextNameStrPtr);
		if (string.IsNullOrEmpty(assemblyContextName))
		{
			ArgumentException.ThrowIfNullOrEmpty(assemblyContextName);
			return;
		}

		var path = Marshal.PtrToStringUTF8(pathStrPtr);
		if (string.IsNullOrEmpty(path))
		{
			ArgumentException.ThrowIfNullOrEmpty(path);
			return;
		}

		var loadContext = AssemblyContext.GetContext(assemblyContextName);
		if (loadContext == null)
		{
			ArgumentNullException.ThrowIfNull(loadContext);
			return;
		}

		AssemblyContext.LoadAssemblyFromPath(path, loadContext);
	}

	[UnmanagedCallersOnly]
	public static unsafe void LoadAssemblyFromBytes(IntPtr assemblyContextNameStrPtr, byte* assemblyBytePtr, int assemblyBytesLength)
	{
		var assemblyContextName = Marshal.PtrToStringUTF8(assemblyContextNameStrPtr);
		if (string.IsNullOrEmpty(assemblyContextName))
		{
			ArgumentException.ThrowIfNullOrEmpty(assemblyContextName);
			return;
		}

		if (assemblyBytePtr == null)
			throw new ArgumentException("Assembly bytes are nullptr");

		var assembly = NativeHelpers.PointerToByteArray(assemblyBytePtr, assemblyBytesLength);

		var loadContext = AssemblyContext.GetContext(assemblyContextName);
		if (loadContext == null)
		{
			ArgumentNullException.ThrowIfNull(loadContext);
			return;
		}

		AssemblyContext.LoadAssemblyFromBytes(assembly, loadContext);
	}
}