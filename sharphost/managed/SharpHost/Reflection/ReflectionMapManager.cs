using System.Runtime.Loader;

namespace SharpHost.Reflection;

public static class ReflectionMapManager
{
	private static readonly Dictionary<AssemblyLoadContext, ReflectionMap> ReflectionCache = [];
	public static List<ReflectionMap> Maps => [.. ReflectionCache.Values];

	public static ReflectionMap? GetReflectionMap(AssemblyLoadContext context)
	{
		if (!ReflectionCache.ContainsKey(context)) return null;
		var cacheMap = ReflectionCache.First(cache => cache.Key == context);
		return cacheMap.Value;
	}

	public static void ResetMap(AssemblyLoadContext context)
	{
		if (!ReflectionCache.ContainsKey(context)) return;

		var map = GetReflectionMap(context)!;
		map.ResetMap();
	}

	public static void RemoveMap(AssemblyLoadContext context)
	{
		if (!ReflectionCache.ContainsKey(context)) return;

		ResetMap(context);
		ReflectionCache.Remove(context);
	}

	public static void AddMap(AssemblyLoadContext context)
	{
		if (ReflectionCache.ContainsKey(context))
			RemoveMap(context);

		var reflectionMap = new ReflectionMap();
		reflectionMap.BuildReflectionMap(context);

		ReflectionCache.Add(context, reflectionMap);
	}

	public static void RebuildMaps()
	{
		foreach (var (context, map) in ReflectionCache)
		{
			map.ResetMap();
			map.BuildReflectionMap(context);
		}
	}
}