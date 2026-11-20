namespace SharpHost.Reflection.Scanners;

public static class ConstructorScanner
{
	public static List<ReflectedConstructor> GetConstructors(Type type)
	{
		List<ReflectedConstructor> constructors = [];
		foreach (var constructor in type.GetConstructors())
		{
			var attributes = AttributeScanner.GetAttributes(constructor, instantiate: true);
			var reflectedConstructor = new ReflectedConstructor()
			{
				Attributes = attributes,
				ConstructorInfo = constructor,
				Metadata = new ReflectionMetadata()
				{
					Name = constructor.Name,
					AssemblyName = type.Assembly.GetName().Name,
					FullName = type.FullName,
					Namespace = type.Namespace,
					IsAbstract = constructor.IsAbstract,
					IsInternal = type.IsNotPublic,
					IsPrivate = constructor.IsPrivate,
					IsStatic = constructor.IsStatic,
					IsPublic = constructor.IsPublic,
					IsSealed = type.IsSealed,
					ObjectType = type
				},
				Parameters = ParameterScanner.GetParameters(constructor.GetParameters())
			};

			constructors.Add(reflectedConstructor);
		}

		return constructors;
	}
}