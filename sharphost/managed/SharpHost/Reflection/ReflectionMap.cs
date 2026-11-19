using System.Reflection;
using System.Runtime.Loader;
using SharpHost.Reflection.Scanners;

namespace SharpHost.Reflection;

public class ReflectionMap
{
	private readonly List<ReflectedAssembly> _reflectedAssemblies = [];

	public void ResetMap() => _reflectedAssemblies.Clear();
	public List<ReflectedAssembly> GetReflectedAssemblies => _reflectedAssemblies;

	public void BuildReflectionMap(AssemblyLoadContext context)
	{
		ResetMap();

		foreach (var assembly in context.Assemblies)
		{
			var assemblyName = assembly.GetName();
			var assemblyMetaData = new ReflectionMetaData()
			{
				FullName = assemblyName.FullName,
				AssemblyName = assemblyName.Name,
				ObjectType = assembly.GetType()
			};

			List<ReflectedClass> reflectedClasses = [];
			List<ReflectedStruct> reflectedStructs = [];
			List<ReflectedEnum> reflectedEnums = [];

			foreach (var type in assembly.GetTypes())
			{
				if (type.IsClass)
				{
					var reflectedClass = ClassScanner.GetClass(type, isDeepScan: true);
					if (reflectedClass == null) continue;

					reflectedClasses.Add(reflectedClass);
					continue;
				}

				if (type.IsEnum)
				{
					var reflectedEnum = EnumScanner.GetReflectedEnum(type);
					if (reflectedEnum == null) continue;

					reflectedEnums.Add(reflectedEnum);
					continue;
				}
			}

			var reflectedAssembly = new ReflectedAssembly()
			{
				MetaData = assemblyMetaData,
				Classes = reflectedClasses,
				Enums = reflectedEnums
			};

			_reflectedAssemblies.Add(reflectedAssembly);
		}
	}
}