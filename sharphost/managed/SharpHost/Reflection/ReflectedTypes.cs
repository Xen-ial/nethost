using System.Reflection;

namespace SharpHost.Reflection;

public class ReflectionMetaData
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
}

public class Parameter
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
}

public class ReflectedAttribute
{
	public ReflectionMetaData MetaData = new();

	public List<object?> ConstructorArguments = [];
	public Dictionary<string, object?> NamedArguments = [];

	public Attribute? Instance = null;
}

public class ReflectedConstructor
{
	public ReflectionMetaData MetaData = new();

	public List<Parameter> Parameters = [];
	public List<ReflectedAttribute> Attributes = [];

	public ConstructorInfo? ConstructorInfo = null;
}

public class ReflectedFunction
{
	public ReflectionMetaData MetaData = new();

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
}

public class ReflectedField
{
	public ReflectionMetaData MetaData = new();

	public List<ReflectedAttribute> Attributes = [];

	public Type? FieldType = null;
	public object? Value = null;

	public bool IsStatic = false;
	public bool IsConst = false;

	public FieldInfo? FieldInfo = null;
}

public class ReflectedProperty
{
	public ReflectionMetaData MetaData = new();

	public List<ReflectedAttribute> Attributes = [];

	public Type? PropertyType = null;
	public object? Value = null;

	public bool CanRead = false;
	public bool CanWrite = false;
	public bool IsStatic = false;

	public PropertyInfo? PropertyInfo = null;
}

public class ReflectedStruct
{
	public ReflectionMetaData MetaData = new();

	public Type? BaseType = null;

	public List<Type> Interfaces = [];
	public List<ReflectedConstructor> Constructors = [];

	public List<ReflectedAttribute> Attributes = [];

	public List<ReflectedClass> Calsses = [];
	public List<ReflectedField> Fields = [];
	public List<ReflectedProperty> Properties = [];
	public List<ReflectedStruct> Structs = [];
	public List<ReflectedFunction> Functions = [];
	public List<ReflectedEnum> Enums = [];
}

public class Enumerator
{
	public string? Member = string.Empty;
	public object? Value = null;
}

public class ReflectedEnum
{
	public ReflectionMetaData MetaData = new();
	public List<Enumerator> Enumerators = [];
}

public class ReflectedClass
{
	public ReflectionMetaData MetaData = new();

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
}

public class ReflectedAssembly
{
	public ReflectionMetaData MetaData = new();
    
	public List<ReflectedClass> Classes = [];
	public List<ReflectedStruct> Structs = [];
	public List<ReflectedEnum> Enums = [];

	public void Reset()
	{
        Classes.Clear();
        Structs.Clear();
		Enums.Clear();
	}
}