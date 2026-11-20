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
					FullName = field.FieldType.FullName,
					Namespace = field.FieldType.Namespace,
					IsAbstract = field.FieldType.IsAbstract,
					IsPrivate = field.IsPrivate,
					IsInternal = field.FieldType.IsNotPublic,
					IsPublic = field.IsPublic,
					IsSealed = field.FieldType.IsSealed,
					IsStatic = field.IsStatic,
					ObjectType = field.GetType()
				},
			};

			fields.Add(reflectedField);
		}

		return fields;
	}
}