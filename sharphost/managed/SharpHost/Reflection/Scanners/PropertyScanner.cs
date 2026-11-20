using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class PropertyScanner
{
	public static List<ReflectedProperty> GetProperties(Type type)
	{
		List<ReflectedProperty> properties = [];
		const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static;

		foreach (var prop in type.GetProperties(flags))
		{
			var reflectedProperty = new ReflectedProperty()
			{
				Attributes = AttributeScanner.GetAttributes(prop, instantiate: true),
				CanRead = prop.CanRead,
				CanWrite = prop.CanWrite,
				IsStatic = prop.GetAccessors(nonPublic: true).Any(acc => acc.IsStatic),
				Metadata = new ReflectionMetadata()
				{
					Name = prop.Name,
					AssemblyName = prop.GetType().Assembly.FullName,
					FullName = prop.GetType().FullName,
					IsAbstract = prop.GetType().IsAbstract,
					IsInternal = prop.GetType().IsNotPublic,
					IsPrivate = !prop.GetType().IsPublic,
					IsPublic = prop.GetType().IsPublic,
					IsSealed = prop.GetType().IsSealed,
					IsStatic = prop.GetAccessors(nonPublic: true).Any(acc => acc.IsStatic),
					Namespace = prop.GetType().Namespace,
					ObjectType = prop.PropertyType
				},
				PropertyInfo = prop,
				PropertyType = prop.PropertyType,
			};

			properties.Add(reflectedProperty);
		}

		return properties;
	}
}