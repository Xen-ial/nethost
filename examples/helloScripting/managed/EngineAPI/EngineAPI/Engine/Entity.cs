using EngineAPI.Engine.Scripting;

namespace EngineAPI.Engine;

public class Entity(int entityId)
{
	public int Id() => entityId;

	private readonly List<Component> _componentData = [];
	private readonly List<Script> _scripts = [];

	public List<Component> Components => _componentData;
	public List<Script> Scripts() => _scripts;

	public T? GetComponent<T>() where T : Component
	{
		var component = _componentData.FirstOrDefault(comp => comp is T);
		return component as T;
	}

	public T? AddComponent<T>() where T : Component, new()
	{
		var component = GetComponent<T>();
		if (component == null)
			_componentData.Add(new T());

		return GetComponent<T>();
	}

	public T? AddComponent<T>(T component) where T : Component, new()
	{
		if (!_componentData.Contains(component))
			_componentData.Add(component);

		return GetComponent<T>();
	}

	public void RemoveComponent<T>() where T : Component
	{
		var component = GetComponent<T>();
		if (component == null)
			return;

		_componentData.Remove(component);
	}

	public void RemoveComponent<T>(T component) where T : Component
	{
		if (!_componentData.Contains(component))
			return;

		_componentData.Remove(component);
	}

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
}