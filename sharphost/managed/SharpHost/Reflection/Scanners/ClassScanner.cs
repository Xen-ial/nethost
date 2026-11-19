using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class ClassScanner
{
	public static ReflectedClass? GetClass(Type type, bool isDeepScan = false)
	{
		if (!type.IsClass) return null;

		var refClass = UnwrapClass(type);
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic;

		foreach (var nestedType in type.GetNestedTypes(flags))
		{
			if (!nestedType.IsClass) continue;

			if (isDeepScan)
			{
				var nestedRefClass = GetClass(nestedType, isDeepScan: true);
				if (nestedRefClass != null)
					refClass.Classes.Add(nestedRefClass);

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
			MetaData = new ReflectionMetaData()
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
			Attributes = AttributeScanner.GetAttributes(type, instantiate: true),
			BaseType = type.BaseType,
			Classes = [],
			Constructors = ConstructorScanner.GetConstructors(type),
			Enums = EnumScanner.GetReflectedEnums(type),
            Fields = FieldScanner.GetFields(type),
		};

		return reflectedClass;
	}
}