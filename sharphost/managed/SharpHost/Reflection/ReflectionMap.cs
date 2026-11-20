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
			var assemblyMetadata = new ReflectionMetadata()
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
					if (!reflectedClass.HasValue) continue;

					reflectedClasses.Add(reflectedClass.Value);
					continue;
				}

				if (type.IsEnum)
				{
					var reflectedEnum = EnumScanner.GetReflectedEnum(type);
					if (!reflectedEnum.HasValue) continue;

					reflectedEnums.Add(reflectedEnum.Value);
					continue;
				}

				if (StructScanner.IsStruct(type))
				{
					var reflectedStruct = StructScanner.GetStruct(type);
					if (!reflectedStruct.HasValue) continue;

					reflectedStructs.Add(reflectedStruct.Value);
				}
			}

			var reflectedAssembly = new ReflectedAssembly()
			{
				Metadata = assemblyMetadata,
				Classes = reflectedClasses,
				Enums = reflectedEnums,
				Structs = reflectedStructs
			};

			_reflectedAssemblies.Add(reflectedAssembly);
		}
	}
}