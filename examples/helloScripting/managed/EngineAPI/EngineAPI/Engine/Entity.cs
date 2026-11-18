using EngineAPI.Engine.Scripting;

namespace EngineAPI.Engine;

public class Entity(int entityId)
{
	public int Id() => entityId;
	private readonly List<Script> _scripts = [];

	public List<Script> Scripts() => _scripts;

	public T? GetScript<T>() where T : Script
	{
		var script = _scripts.FirstOrDefault(scr => scr is T);
		return script as T;
	}

	public void AddScript(Script script)
	{
		if (!_scripts.Contains(script))
			_scripts.Add(script);

		script.Owner = this;
	}

	public void AddScript<T>() where T : Script, new()
	{
		var script = GetScript<T>();
		if (script == null)
			_scripts.Add(new T());

		script = GetScript<T>()!;
		script.Owner = this;
	}

	public void AddScript<T>(T script) where T : Script
	{
		if (!_scripts.Contains(script))
			_scripts.Add(script);

		script = GetScript<T>()!;
		script.Owner = this;
	}

	public void RemoveScript<T>() where T : Script
	{
		var script = GetScript<T>();
		if (script == null)
			return;

		_scripts.Remove(script);
	}

	public void RemoveScript<T>(T script) where T : Script
	{
		if (!_scripts.Contains(script))
			return;

		_scripts.Remove(script);
	}

	public void RemoveScript(Type scriptType)
	{
		var script = _scripts.FirstOrDefault(type => type.GetType() == scriptType);

		if (script == null)
			return;

		_scripts.Remove(script);
	}
}