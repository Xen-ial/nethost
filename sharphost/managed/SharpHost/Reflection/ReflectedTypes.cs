using System.Reflection;
using System.Runtime.InteropServices;

namespace SharpHost.Reflection;

[StructLayout(LayoutKind.Sequential)]
public struct ReflectionMetadata
{
	public string? Name = string.Empty;
	public string? Namespace = string.Empty;
	public string? AssemblyName = string.Empty;
	public string? FullName = string.Empty;

	public bool IsPublic = false;
	public bool IsPrivate = false;
	public bool IsInternal = false;
	public bool IsAbstract = false;
	public bool IsSealed = false;
	public bool IsStatic = false;

	public Type? ObjectType = null;

	public ReflectionMetadata()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct Parameter
{
	public string? Name = string.Empty;

	public Type? ParamType = null;
	public object? DefaultValue = null;

	public bool IsOptional = false;
	public bool IsByRef = false;
	public bool IsIn = false;
	public bool IsOut = false;

	public List<ReflectedAttribute> Attributes = [];

	public ParameterInfo? ParameterInfo = null;

	public Parameter()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedAttribute
{
	public ReflectionMetadata Metadata = new();

	public List<object?> ConstructorArguments = [];
	public Dictionary<string, object?> NamedArguments = [];

	public Attribute? Instance = null;

	public ReflectedAttribute()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedConstructor
{
	public ReflectionMetadata Metadata = new();

	public List<Parameter> Parameters = [];
	public List<ReflectedAttribute> Attributes = [];

	public ConstructorInfo? ConstructorInfo = null;

	public ReflectedConstructor()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedFunction
{
	public ReflectionMetadata Metadata = new();

	public Type? ReturnType = null;

	public List<Parameter> Parameters = [];
	public List<ReflectedAttribute> Attributes = [];
	public List<Type> GenericArguments = [];

	public bool IsStatic = false;
	public bool IsAsync = false;
	public bool IsVirtual = false;
	public bool IsAbstract = false;
	public bool IsOverride = false;
	public bool IsGeneric = false;

	public MethodInfo? Info = null;
	public Delegate? CompiledDelegate = null;

	public ReflectedFunction()
	{
	}
}

public struct ReflectedField
{
	public ReflectionMetadata Metadata = new();

	public List<ReflectedAttribute> Attributes = [];

	public Type? FieldType = null;

	public bool IsStatic = false;
	public bool IsConst = false;

	public FieldInfo? FieldInfo = null;

	public ReflectedField()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedProperty
{
	public ReflectionMetadata Metadata = new();

	public List<ReflectedAttribute> Attributes = [];

	public Type? PropertyType = null;

	public bool CanRead = false;
	public bool CanWrite = false;
	public bool IsStatic = false;

	public PropertyInfo? PropertyInfo = null;

	public ReflectedProperty()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedStruct
{
	public ReflectionMetadata Metadata = new();

	public Type? BaseType = null;

	public List<Type> Interfaces = [];
	public List<ReflectedConstructor> Constructors = [];

	public List<ReflectedAttribute> Attributes = [];

	public List<ReflectedClass> Classes = [];
	public List<ReflectedField> Fields = [];
	public List<ReflectedProperty> Properties = [];
	public List<ReflectedStruct> Structs = [];
	public List<ReflectedFunction> Functions = [];
	public List<ReflectedEnum> Enums = [];

	public ReflectedStruct()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct Enumerator
{
	public string? Member = string.Empty;
	public object? Value = null;

	public Enumerator()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedEnum
{
	public ReflectionMetadata Metadata = new();
	public List<Enumerator> Enumerators = [];

	public ReflectedEnum()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedClass
{
	public ReflectionMetadata Metadata = new();

	public Type? BaseType = null;

	public List<Type> Interfaces = [];
	public List<ReflectedConstructor> Constructors = [];

	public List<ReflectedAttribute> Attributes = [];

	public List<ReflectedFunction> Functions = [];
	public List<ReflectedField> Fields = [];
	public List<ReflectedProperty> Properties = [];
	public List<ReflectedEnum> Enums = [];
	public List<ReflectedStruct> Structs = [];
	public List<ReflectedClass> Classes = [];

	public ReflectedClass()
	{
	}
}

[StructLayout(LayoutKind.Sequential)]
public struct ReflectedAssembly
{
	public ReflectionMetadata Metadata = new();

	public List<ReflectedClass> Classes = [];
	public List<ReflectedStruct> Structs = [];
	public List<ReflectedEnum> Enums = [];

	public ReflectedAssembly()
	{
	}

	public void Reset()
	{
		Classes.Clear();
		Structs.Clear();
		Enums.Clear();
	}
}