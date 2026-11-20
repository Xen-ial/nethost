using System.Linq.Expressions;
using System.Reflection;
using System.Runtime.CompilerServices;

namespace SharpHost.Reflection.Scanners;

public static class FunctionScanner
{
	public static List<ReflectedFunction> GetFunctions(Type type)
	{
		List<ReflectedFunction> functions = [];
		const BindingFlags flags =
			BindingFlags.Public | BindingFlags.NonPublic |
			BindingFlags.Instance | BindingFlags.Static |
			BindingFlags.DeclaredOnly;

		foreach (var func in type.GetMethods(flags))
		{
			var reflectedFunction = new ReflectedFunction()
			{
				Attributes = AttributeScanner.GetAttributes(func, instantiate: true),
				CompiledDelegate = CreateDynamicDelegate(func),
				GenericArguments = [.. func.GetGenericArguments()],
				Info = func,
				IsAbstract = func.IsAbstract,
				IsAsync = IsAsync(func),
				IsGeneric = func.IsGenericMethod,
				IsOverride = IsOverride(func),
				IsStatic = func.IsStatic,
				IsVirtual = func.IsVirtual,
				ReturnType = func.ReturnType,
				Parameters = ParameterScanner.GetParameters(func.GetParameters()),
				MetaData = new ReflectionMetaData()
				{
					Name = func.Name,
					AssemblyName = func.GetType().Assembly.GetName().Name,
					FullName = func.GetType().FullName,
					IsAbstract = func.IsAbstract,
					IsInternal = func.GetType().IsNotPublic,
					IsPrivate = func.IsPrivate,
					IsPublic = func.IsPublic,
					IsSealed = func.GetType().IsSealed,
					IsStatic = func.IsStatic,
					Namespace = func.GetType().Namespace,
					ObjectType = func.GetType()
				}
			};

			functions.Add(reflectedFunction);
		}

		return functions;
	}

	private static Delegate CreateDynamicDelegate(MethodInfo methodInfo, object? target = null)
	{
		var types = methodInfo.GetParameters()
			.Select(paramInfo => paramInfo.ParameterType)
			.ToList();

		if (!methodInfo.IsStatic && target == null)
			types.Insert(0, methodInfo.DeclaringType!);

		types.Add(methodInfo.ReturnType);
		var delegateType = Expression.GetDelegateType([.. types]);

		return methodInfo.CreateDelegate(delegateType, target);
	}

	private static bool IsAsync(MethodInfo info)
	{
		return info.GetCustomAttribute<AsyncStateMachineAttribute>() != null;
	}

	private static bool IsOverride(MethodInfo info)
	{
		return info.GetBaseDefinition().DeclaringType != info.DeclaringType;
	}
}