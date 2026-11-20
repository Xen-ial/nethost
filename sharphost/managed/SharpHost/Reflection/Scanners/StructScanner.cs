using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class StructScanner
{
	public static List<ReflectedStruct> GetStructs(Type type, bool isDeepScan = false)
	{
		List<ReflectedStruct> structs = [];
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic |
		                           BindingFlags.Instance | BindingFlags.Static |
		                           BindingFlags.DeclaredOnly;

		foreach (var structType in type.GetNestedTypes(flags))
		{
            if (!IsStruct(type)) continue;
            var reflectedStruct = GetStruct(structType, isDeepScan);
            
            if (!reflectedStruct.HasValue) continue;
            structs.Add(reflectedStruct.Value);
		}

		return structs;
	}

	public static ReflectedStruct? GetStruct(Type type, bool isDeepScan = false)
	{
		if (!IsStruct(type)) return null;
		var refStruct = UnwrapStruct(type);
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic |
		                           BindingFlags.Instance | BindingFlags.Static |
		                           BindingFlags.DeclaredOnly;

		foreach (var nestedType in type.GetNestedTypes(flags))
		{
			if (!IsStruct(nestedType)) continue;
			if (isDeepScan)
			{
				var nestedRefStruct = GetStruct(nestedType, isDeepScan: true);
				if (nestedRefStruct.HasValue)
					refStruct.Structs.Add(nestedRefStruct.Value);

				continue;
			}

			refStruct.Structs.Add(UnwrapStruct(nestedType));
		}

		return refStruct;
	}

	private static ReflectedStruct UnwrapStruct(Type type)
	{
		var reflectedStruct = new ReflectedStruct()
		{
			Attributes = AttributeScanner.GetAttributes(type, instantiate: true),
			BaseType = type.BaseType,
			Classes = ClassScanner.GetClasses(type, isDeepScan: true),
			Constructors = ConstructorScanner.GetConstructors(type),
			Enums = EnumScanner.GetReflectedEnums(type),
			Fields = FieldScanner.GetFields(type),
			Functions = FunctionScanner.GetFunctions(type),
			Interfaces = [.. type.GetInterfaces()],
			Metadata = new ReflectionMetadata()
			{
				Name = type.Name,
				Namespace = type.Namespace,
				AssemblyName = type.Assembly.FullName,
				FullName = type.FullName,
				IsAbstract = type.IsAbstract,
				IsInternal = type.IsNotPublic,
				IsPrivate = !type.IsPublic,
				IsSealed = type.IsSealed,
				IsPublic = type.IsPublic,
				ObjectType = type
			},
			Properties = PropertyScanner.GetProperties(type),
			Structs = []
		};

		return reflectedStruct;
	}

	public static bool IsStruct(Type type)
	{
		return type is { IsValueType: true, IsEnum: false, IsPrimitive: false };
	}
}