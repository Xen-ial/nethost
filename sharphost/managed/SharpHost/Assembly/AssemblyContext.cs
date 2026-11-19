using System.Runtime.Loader;

namespace SharpHost.Assembly;

public class AssemblyContext
{
	private List<AssemblyLoadContext> _assemblyLoadContexts = [];

	public void CreateAssemblyLoadContext(string name)
	{
		var loadContext = new AssemblyLoadContext(name, isCollectible: true);
		_assemblyLoadContexts.Add(loadContext);
	}

	public void UnloadAndDestroyAssemblyContext(string name)
	{
		var loadContext = _assemblyLoadContexts.FirstOrDefault(context => context.Name == name);
		if (loadContext == null) return;

		loadContext.Unload();
		_assemblyLoadContexts.Remove(loadContext);
	}

	public void LoadAssemblyFromPath(string path, AssemblyLoadContext context)
	{
		context.LoadFromAssemblyPath(path);
	}

	public void LoadAssemblyFromBytes(byte[] assemblyBytes, AssemblyLoadContext context)
	{
		using var stream = new MemoryStream(assemblyBytes);
		context.LoadFromStream(stream);
	}

	public AssemblyLoadContext? GetContext(string name)
	{
		return _assemblyLoadContexts.FirstOrDefault(context => context.Name == name);
	}
}