using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace SharpHost.Reflection;

public static unsafe class ReflectionExporter
{
	public static void GetAssemblyMetadata(byte** outBuffer, int* outLength)
	{
	}

	public static void FreeMetadataBuffer(byte* buffer)
	{
		NativeMemory.Free(buffer);
	}
}