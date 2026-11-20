using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class FieldScanner
{
	public static List<ReflectedField> GetFields(Type targetType)
	{
		List<ReflectedField> fields = [];
		const BindingFlags flags =
			BindingFlags.Public |
			BindingFlags.NonPublic |
			BindingFlags.Instance |
			BindingFlags.Static;

		foreach (var field in targetType.GetFields(flags))
		{
			var declaringType = field.DeclaringType;
			var reflectedField = new ReflectedField()
			{
				Attributes = AttributeScanner.GetAttributes(field, instantiate: true),
				FieldInfo = field,
				FieldType = field.FieldType,
				IsConst = field is { IsLiteral: true, IsInitOnly: false },
				IsStatic = field.IsStatic,
				Metadata = new ReflectionMetadata()
				{
					AssemblyName = field.FieldType.Assembly.GetName().Name,
					Name = field.Name,
					FullName = declaringType != null ? $"{declaringType.FullName}.{field.Name}" : field.Name,
					Namespace = declaringType != null ? declaringType.Namespace : targetType.Namespace,
					IsAbstract = declaringType?.IsAbstract ?? false,
					IsPrivate = field.IsPrivate,
					IsInternal = declaringType?.IsNotPublic ?? false,
					IsPublic = field.IsPublic,
					IsSealed = declaringType?.IsSealed ?? false,
					IsStatic = field.IsStatic,
					ObjectType = field.FieldType
				},
			};

			fields.Add(reflectedField);
		}

		return fields;
	}
}