using System.Reflection;

namespace SharpHost.Reflection.Scanners;

public static class ParameterScanner
{
	public static List<Parameter> GetParameters(ParameterInfo[] parameters)
	{
		List<Parameter> parameterList = [];
		foreach (var param in parameters)
		{
			var paramAttributes = AttributeScanner.GetAttributes(param, instantiate: true);
			var parameter = new Parameter()
			{
				Attributes = paramAttributes,
				DefaultValue = param.DefaultValue,
                HasDefaultValue = param.HasDefaultValue,
				IsOptional = param.IsOptional,
				IsOut = param.IsOut,
				IsIn = param.IsIn,
				IsByRef = param.ParameterType.IsByRef,
				Name = param.Name,
				ParamType = param.ParameterType,
				ParameterInfo = param
			};

			parameterList.Add(parameter);
		}

		return parameterList;
	}
}