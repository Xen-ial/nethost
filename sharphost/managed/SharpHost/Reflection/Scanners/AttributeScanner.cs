using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class AttributeScanner
{
	public static List<ReflectedAttribute> GetAttributes(MemberInfo memberInfo, bool instantiate = false)
	{
		var attrData = CustomAttributeData.GetCustomAttributes(memberInfo);
		var instance = instantiate
			? memberInfo.GetCustomAttributes(inherit: false).OfType<Attribute>().ToList()
			: [];

		return BuildAttributes(attrData, instance);
	}

	public static List<ReflectedAttribute> GetAttributes(ParameterInfo paramInfo, bool instantiate = false)
	{
		var attrData = CustomAttributeData.GetCustomAttributes(paramInfo);
		var instance = instantiate
			? paramInfo.GetCustomAttributes(inherit: false).OfType<Attribute>().ToList()
			: [];

		return BuildAttributes(attrData, instance);
	}

	private static List<ReflectedAttribute> BuildAttributes(
		IList<CustomAttributeData> dataList,
		List<Attribute> instances)
	{
		var results = new List<ReflectedAttribute>(dataList.Count);

		for (int i = 0; i < dataList.Count; i++)
		{
			var data = dataList[i];
			var attrType = data.AttributeType;

			if (attrType.Namespace?.StartsWith("System.Runtime.CompilerServices") == true)
				continue;

			var reflectedAttr = new ReflectedAttribute()
			{
				MetaData = new ReflectionMetaData()
				{
					Name = attrType.Name,
					AssemblyName = attrType.Assembly.FullName,
					FullName = attrType.FullName,
					ObjectType = attrType,
					IsPublic = attrType.IsPublic,
					IsAbstract = attrType.IsAbstract,
					IsInternal = attrType.IsNotPublic,
					IsPrivate = !attrType.IsPublic,
					IsSealed = attrType.IsSealed
				},
				Instance = i < instances.Count ? instances[i] : null
			};

			foreach (var argument in data.ConstructorArguments)
				reflectedAttr.ConstructorArguments.Add(UnwrapArgValue(argument));

			foreach (var namedArg in data.NamedArguments)
				reflectedAttr.NamedArguments[namedArg.MemberName] = UnwrapArgValue(namedArg.TypedValue);

			results.Add(reflectedAttr);
		}

		return results;
	}

	private static object? UnwrapArgValue(CustomAttributeTypedArgument arg)
	{
		if (arg.Value is IReadOnlyCollection<CustomAttributeTypedArgument> arrArgs)
			return arrArgs.Select(UnwrapArgValue).ToArray();

		return arg.Value;
	}
}