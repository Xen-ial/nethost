using System.Reflection;
using System.Runtime.InteropServices;
using EngineAPI.Engine;
using EngineAPI.Engine.Scripting;

namespace EngineAPI.Native;

public static class NativeBridge
{
	public static readonly List<Entity> Entities = [];

	public static void CreateEntity(int id)
	{
		Entities.Add(new Entity(id));
	}

	public static void DestroyEntity(int id)
	{
		var entity = Entities.FirstOrDefault(ent => ent.Id() == id);
		if (entity != null)
			Entities.Remove(entity);
	}

	public static void PrintAllEntities()
	{
		foreach (var entity in Entities)
		{
			Console.WriteLine($"Entity: {entity.Id()}");
		}

		Console.WriteLine($"Total Entities: {Entities.Count}");
	}

	public static Entity? GetEntity(int entityId)
	{
		var entity = Entities.FirstOrDefault(ent => ent.Id() == entityId);
		return entity;
	}

	public static void UpdateScripts()
	{
		foreach (var entity in Entities)
		foreach (var script in entity.Scripts())
			script.Update(1.11F);
	}

	public static void AddScript(IntPtr scriptName, Entity entity, Assembly[] assemblies)
	{
		var scriptBaseType = typeof(Script);
		var scriptTypes = assemblies
			.SelectMany(types => types.GetTypes())
			.Where(type => scriptBaseType.IsAssignableFrom(type) && type is { IsClass: true, IsAbstract: false });

		var scriptTypeList = scriptTypes.ToList();

		var sName = Marshal.PtrToStringUTF8(scriptName);
		if (sName == null)
		{
			Console.WriteLine("Script name was null.");
		}

		var scriptType = scriptTypeList.FirstOrDefault(type => type.Name == sName);
		if (scriptType == null)
		{
			Console.WriteLine("Script type was null.");
			return;
		}

		if (Activator.CreateInstance(scriptType) is Script script)
			entity.AddScript(script);
	}

	public static void DestroyScript(IntPtr scriptName, Entity entity, Assembly[] assemblies)
	{
		var scriptBaseType = typeof(Script);
		var scriptTypes = assemblies
			.SelectMany(types => types.GetTypes())
			.Where(type => scriptBaseType.IsAssignableFrom(type) && type is { IsClass: true, IsAbstract: false });

		var scriptTypeList = scriptTypes.ToList();

		var sName = Marshal.PtrToStringUTF8(scriptName);
		if (sName == null)
		{
			Console.WriteLine("Script name was null.");
		}

		var scriptType = scriptTypeList.FirstOrDefault(type => type.Name == sName);
		if (scriptType == null)
		{
			Console.WriteLine("Script type was null.");
			return;
		}

		entity.RemoveScript(scriptType);
	}
}