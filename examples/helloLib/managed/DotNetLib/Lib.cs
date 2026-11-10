using System.Runtime.InteropServices;

namespace DotNetLib;

public static class Lib
{
	private static byte _isWaiting = 0;

	[UnmanagedCallersOnly]
	public static void Main()
	{
		Console.WriteLine("Hello World!");
		_isWaiting = 1;
	}

	[UnmanagedCallersOnly]
	public static byte IsWaiting() => _isWaiting;
}