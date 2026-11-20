using System.Reflection;
using System.Text.Json.Serialization;

namespace SharpHost.Reflection;

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

	[JsonIgnore] public Type? ObjectType = null;

	public string? ObjectTypeName => ObjectType?.FullName ?? ObjectType?.Name;

	public ReflectionMetadata()
	{
	}
}

public struct Parameter
{
	public string? Name = string.Empty;

	[JsonIgnore] public Type? ParamType = null;

	public string? ParamTypeName => ParamType?.FullName ?? ParamType?.Name;

	public bool HasDefaultValue = false;
	public object? DefaultValue = null;

	public bool IsOptional = false;
	public bool IsByRef = false;
	public bool IsIn = false;
	public bool IsOut = false;

	public List<ReflectedAttribute> Attributes = [];

	[JsonIgnore] public ParameterInfo? ParameterInfo = null;

	public Parameter()
	{
	}
}

public struct ReflectedAttribute
{
	public ReflectionMetadata Metadata = new();

	public List<object?> ConstructorArguments = [];
	public Dictionary<string, object?> NamedArguments = [];

	[JsonIgnore] public Attribute? Instance = null;

	public ReflectedAttribute()
	{
	}
}

public struct ReflectedConstructor
{
	public ReflectionMetadata Metadata = new();

	public List<Parameter> Parameters = [];
	public List<ReflectedAttribute> Attributes = [];

	[JsonIgnore] public ConstructorInfo? ConstructorInfo = null;

	public ReflectedConstructor()
	{
	}
}

public struct ReflectedFunction
{
	public ReflectionMetadata Metadata = new();

	[JsonIgnore] public Type? ReturnType = null;

	public string? ReturnTypeName => ReturnType?.FullName ?? ReturnType?.Name;

	public List<Parameter> Parameters = [];
	public List<ReflectedAttribute> Attributes = [];

	[JsonIgnore] public List<Type> GenericArguments = [];

	public List<string> GenericArgumentTypeNames => GenericArguments.ConvertAll(type => type.FullName ?? type.Name);

	public bool IsStatic = false;
	public bool IsAsync = false;
	public bool IsVirtual = false;
	public bool IsAbstract = false;
	public bool IsOverride = false;
	public bool IsGeneric = false;

	[JsonIgnore] public MethodInfo? Info = null;

	[JsonIgnore] public Delegate? CompiledDelegate = null;

	public ReflectedFunction()
	{
	}
}

public struct ReflectedField
{
	public ReflectionMetadata Metadata = new();

	public List<ReflectedAttribute> Attributes = [];

	[JsonIgnore] public Type? FieldType = null;

	public string? FieldTypeName => FieldType?.FullName ?? FieldType?.Name;

	public bool IsStatic = false;
	public bool IsConst = false;

	[JsonIgnore] public FieldInfo? FieldInfo = null;

	public ReflectedField()
	{
	}
}

public struct ReflectedProperty
{
	public ReflectionMetadata Metadata = new();

	public List<ReflectedAttribute> Attributes = [];

	[JsonIgnore] public Type? PropertyType = null;

	public string? PropertyTypeName => PropertyType?.FullName ?? PropertyType?.Name;

	public bool CanRead = false;
	public bool CanWrite = false;
	public bool IsStatic = false;

	[JsonIgnore] public PropertyInfo? PropertyInfo = null;

	public ReflectedProperty()
	{
	}
}

public struct ReflectedStruct
{
	public ReflectionMetadata Metadata = new();

	[JsonIgnore] public Type? BaseType = null;

	[JsonIgnore] public List<Type> Interfaces = [];

	public string? BaseTypeName => BaseType?.FullName ?? BaseType?.Name;
	public List<string> InterfaceTypeNames => Interfaces.ConvertAll(type => type.FullName ?? type.Name);

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

public struct Enumerator
{
	public string? Member = string.Empty;
	public object? Value = null;

	public Enumerator()
	{
	}
}

public struct ReflectedEnum
{
	public ReflectionMetadata Metadata = new();
	public List<Enumerator> Enumerators = [];

	public ReflectedEnum()
	{
	}
}

public struct ReflectedClass
{
	public ReflectionMetadata Metadata = new();

	[JsonIgnore] public Type? BaseType = null;

	[JsonIgnore] public List<Type> Interfaces = [];

	public string? BaseTypeName => BaseType?.FullName ?? BaseType?.Name;
	public List<string> InterfaceTypeNames => Interfaces.ConvertAll(type => type.FullName ?? type.Name);

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