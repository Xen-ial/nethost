namespace EngineAPI.Native;

public struct EmptyArgs;

public readonly unsafe struct TypeCall<TReturn, TArgs>(IntPtr ptr)
	where TArgs : struct
{
	public static implicit operator TypeCall<TReturn, TArgs>(IntPtr pointer) => new(pointer);

	public TReturn Invoke() =>
		((delegate* unmanaged[Cdecl]<TReturn>)ptr)();

	public TReturn Invoke<T1>(T1 arg1)
		=> ((delegate* unmanaged[Cdecl]<T1, TReturn>)ptr)(arg1);

	public TReturn Invoke<T1, T2>(TArgs args)
	{
		var (arg1, arg2) = ((T1, T2))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, TReturn>)ptr)(arg1, arg2);
	}

	public TReturn Invoke<T1, T2, T3>(TArgs args)
	{
		var (arg1, arg2, arg3) = ((T1, T2, T3))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, TReturn>)ptr)(arg1, arg2, arg3);
	}

	public TReturn Invoke<T1, T2, T3, T4>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4) = ((T1, T2, T3, T4))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, TReturn>)ptr)(arg1, arg2, arg3, arg4);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5) = ((T1, T2, T3, T4, T5))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5, T6>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6) = ((T1, T2, T3, T4, T5, T6))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5, T6, T7>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7) = ((T1, T2, T3, T4, T5, T6, T7))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5, T6, T7, T8>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) = ((T1, T2, T3, T4, T5, T6, T7, T8))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5, T6, T7, T8, T9>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) = ((T1, T2, T3, T4, T5, T6, T7, T8, T9))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, T9, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	}

	public TReturn Invoke<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) = ((T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))(object)args;
		return ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TReturn>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	}
    
    public bool IsResolved() => ptr != IntPtr.Zero;
}

public readonly unsafe struct VoidCall<TArgs>(IntPtr ptr)
	where TArgs : struct
{
	public static implicit operator VoidCall<TArgs>(IntPtr pointer) => new(pointer);

	public void Invoke()
		=> ((delegate* unmanaged[Cdecl]<void>)ptr)();

	public void Invoke<T1>(T1 arg1)
		=> ((delegate* unmanaged[Cdecl]<T1, void>)ptr)(arg1);

	public void Invoke<T1, T2>(TArgs args)
	{
		var (arg1, arg2) = ((T1, T2))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, void>)ptr)(arg1, arg2);
	}

	public void Invoke<T1, T2, T3>(TArgs args)
	{
		var (arg1, arg2, arg3) = ((T1, T2, T3))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, void>)ptr)(arg1, arg2, arg3);
	}

	public void Invoke<T1, T2, T3, T4>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4) = ((T1, T2, T3, T4))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, void>)ptr)(arg1, arg2, arg3, arg4);
	}

	public void Invoke<T1, T2, T3, T4, T5>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5) = ((T1, T2, T3, T4, T5))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, void>)ptr)(arg1, arg2, arg3, arg4, arg5);
	}

	public void Invoke<T1, T2, T3, T4, T5, T6>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6) = ((T1, T2, T3, T4, T5, T6))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, void>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6);
	}

	public void Invoke<T1, T2, T3, T4, T5, T6, T7>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7) = ((T1, T2, T3, T4, T5, T6, T7))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, void>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	public void Invoke<T1, T2, T3, T4, T5, T6, T7, T8>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) = ((T1, T2, T3, T4, T5, T6, T7, T8))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, void>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}
    
    public void Invoke<T1, T2, T3, T4, T5, T6, T7, T8, T9>(TArgs args)
    {
	    var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) = ((T1, T2, T3, T4, T5, T6, T7, T8, T9))(object)args;
	    ((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, T9, void>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    }

	public void Invoke<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(TArgs args)
	{
		var (arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) = ((T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))(object)args;
		((delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, void>)ptr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	}
    
	public bool IsResolved() => ptr != IntPtr.Zero;
}
