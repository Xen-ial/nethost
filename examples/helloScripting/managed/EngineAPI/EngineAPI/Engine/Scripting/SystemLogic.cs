namespace EngineAPI.Engine.Scripting;

public struct SystemState
{
	public List<Entity> Entities;
}

public abstract class SystemLogic
{
	public abstract void Update(ref SystemState state);
}
