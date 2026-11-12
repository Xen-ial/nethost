namespace EngineAPI.Engine.Scripting;

public abstract class Script
{
	public Entity? Owner = null;

	public abstract void Update(float deltaTime);
	public abstract void OnDraw(float deltaTime);
}