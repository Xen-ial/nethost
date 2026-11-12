using EngineAPI.Engine.Scripting;

namespace EngineAPI.Engine.Components;

public class Transform : Component
{
	private bool _isDirty;

	public Vec3 Position
	{
		get;
		set
		{
			field = value;
			_isDirty = true;
		}
	}

	public Vec3 Scale
	{
		get;
		set
		{
			field = value;
			_isDirty = true;
		}
	}

	public Vec3 Rotation
	{
		get;
		set
		{
			field = value;
			_isDirty = true;
		}
	}

	public bool NeedsToSync()
	{
		if (_isDirty)
		{
			_isDirty = false;
			return true;
		}

		return false;
	}

	public void SetIsDirty(bool isDirty) => _isDirty = isDirty;
}