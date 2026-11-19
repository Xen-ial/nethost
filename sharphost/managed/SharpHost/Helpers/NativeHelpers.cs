namespace SharpHost.Helpers;

public class NativeHelpers
{
	public static unsafe byte[] PointerToByteArray(byte* ptr, int length)
	{
		if (ptr == null || length == 0)
			throw new ArgumentException("Byte PTR is null or Length is equal to 0");

		return new ReadOnlySpan<byte>(ptr, length).ToArray();
	}
}