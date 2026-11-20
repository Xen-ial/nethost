using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class ClassScanner
{
	public static List<ReflectedClass> GetClasses(Type type, bool isDeepScan = false)
	{
		List<ReflectedClass> classes = [];
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic |
		                           BindingFlags.Instance | BindingFlags.Static |
		                           BindingFlags.DeclaredOnly;

		foreach (var classType in type.GetNestedTypes(flags))
		{
			if (!type.IsClass) continue;
			var reflectedClass = GetClass(classType, isDeepScan);

			if (!reflectedClass.HasValue) continue;
			classes.Add(reflectedClass.Value);
		}

		return classes;
	}

	public static ReflectedClass? GetClass(Type type, bool isDeepScan = false)
	{
		if (!type.IsClass) return null;

		var refClass = UnwrapClass(type);
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic |
		                           BindingFlags.Instance | BindingFlags.Static |
		                           BindingFlags.DeclaredOnly;

		foreach (var nestedType in type.GetNestedTypes(flags))
		{
			if (!nestedType.IsClass) continue;

			if (isDeepScan)
			{
				var nestedRefClass = GetClass(nestedType, isDeepScan: true);
				if (nestedRefClass.HasValue)
					refClass.Classes.Add(nestedRefClass.Value);

				continue;
			}

			refClass.Classes.Add(UnwrapClass(nestedType));
		}

		return refClass;
	}

	private static ReflectedClass UnwrapClass(Type type)
	{
		var reflectedClass = new ReflectedClass()
		{
			Metadata = new ReflectionMetadata()
			{
				Name = type.Name,
				Namespace = type.Namespace,
				AssemblyName = type.Assembly.GetName().Name,
				FullName = type.FullName,
				IsAbstract = type.IsAbstract,
				IsInternal = type.IsNotPublic,
				IsPrivate = !type.IsPublic,
				IsSealed = type.IsSealed,
				IsPublic = type.IsPublic,
				IsStatic = type is { IsClass: true, IsAbstract: true, IsSealed: true },
				ObjectType = type
			},
			Attributes = AttributeScanner.GetAttributes(type, instantiate: true),
			BaseType = type.BaseType,
			Classes = [],
			Constructors = ConstructorScanner.GetConstructors(type),
			Enums = EnumScanner.GetReflectedEnums(type),
			Fields = FieldScanner.GetFields(type),
			Functions = FunctionScanner.GetFunctions(type),
			Interfaces = [.. type.GetInterfaces()],
			Properties = PropertyScanner.GetProperties(type),
			Structs = StructScanner.GetStructs(type, isDeepScan: true)
		};

		return reflectedClass;
	}
}