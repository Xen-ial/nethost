using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class EnumScanner
{
	public static List<ReflectedEnum> GetReflectedEnums(Type targetType)
	{
		List<ReflectedEnum> reflectedEnums = [];
        
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic;
		foreach (var type in targetType.GetNestedTypes(flags))
		{
			if (!type.IsEnum) continue;
			
			var reflectedEnum = GetReflectedEnum(type);
            if (!reflectedEnum.HasValue) continue;
            
            reflectedEnums.Add(reflectedEnum.Value);
		}

		return reflectedEnums;
	}

	public static ReflectedEnum? GetReflectedEnum(Type enumType)
	{
		if (!enumType.IsEnum) return null;

		List<Enumerator> enumerators = [];
		var underlyingType = Enum.GetUnderlyingType(enumType);

		foreach (var value in Enum.GetValues(enumType))
		{
			var name = Enum.GetName(enumType, value);
			var rawValue = Convert.ChangeType(value, underlyingType);

			var enumerator = new Enumerator()
			{
				Member = name,
				Value = rawValue
			};

			enumerators.Add(enumerator);
		}

		var reflectedEnum = new ReflectedEnum()
		{
			Enumerators = enumerators,
			Metadata = new ReflectionMetadata()
			{
				Name = enumType.Name,
				Namespace = enumType.Namespace,
				AssemblyName = enumType.Assembly.FullName,
				FullName = enumType.FullName,
				IsAbstract = enumType.IsAbstract,
				IsInternal = enumType.IsNotPublic,
				IsPrivate = !enumType.IsPublic,
				IsPublic = enumType.IsPublic,
				IsSealed = enumType.IsSealed,
				ObjectType = enumType
			}
		};

		return reflectedEnum;
	}
}