using System.Reflection;
using System.Runtime.InteropServices;
using EngineAPI.Engine;
using EngineAPI.Engine.Components;
using EngineAPI.Engine.Scripting;

namespace EngineAPI.Native;

[StructLayout(LayoutKind.Sequential)]
public struct NativeFuncPointers
{
	public IntPtr PSyncTransformFn;
	public IntPtr PSyncBackTransformFn;
}

public static class NativeBridge
{
	private static VoidCall<(int, Vec3, Vec3, Vec3)> _syncTransformFn;
	private static TypeCall<(Vec3, Vec3, Vec3), int> _syncBackTransformFn;

	public static readonly List<Entity> Entities = [];
	public static readonly List<SystemLogic> Systems = [];

	private static SystemState _state;

	public static int InitalizeHostCallbacks(NativeFuncPointers funcs)
	{
		_syncTransformFn = funcs.PSyncTransformFn;
		_syncBackTransformFn = funcs.PSyncBackTransformFn;
		return 0;
	}

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

		_state.Entities = Entities;
		foreach (var system in Systems)
		{
			system.Update(ref _state);
		}
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

	public static void SyncTransform(Entity entity, Transform transform)
	{
		if (!_syncTransformFn.IsResolved())
			return;

		_syncTransformFn.Invoke<Vec3, Vec3, Vec3>((entity.Id(), transform.Position, transform.Scale, transform.Rotation));
	}

	public static Transform SyncBackTransform(Entity entity)
	{
		if (!_syncBackTransformFn.IsResolved())
			return new Transform();

		var (postion, scale, rotation) = _syncBackTransformFn.Invoke(entity.Id());
		var transform = new Transform
		{
			Position = postion,
			Scale = scale,
			Rotation = rotation
		};

		return transform;
	}
}