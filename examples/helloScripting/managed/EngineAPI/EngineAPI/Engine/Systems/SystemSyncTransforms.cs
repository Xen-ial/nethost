using EngineAPI.Engine.Components;
using EngineAPI.Engine.Scripting;
using EngineAPI.Native;

namespace EngineAPI.Engine.Systems;

public class SystemSyncTransfoms : SystemLogic
{
	public override void Update(ref SystemState data)
	{
		foreach (var entity in data.Entities)
		{
			var transform = entity.GetComponent<Transform>();
			if (transform == null)
				continue;

			if (transform.NeedsToSync())
				NativeBridge.SyncTransform(entity, transform);

			var rendererTransform = NativeBridge.SyncBackTransform(entity);
			transform.Position = rendererTransform.Position;
			transform.Rotation = rendererTransform.Rotation;
			transform.Scale = rendererTransform.Scale;

			transform.SetIsDirty(false);
		}
	}
}