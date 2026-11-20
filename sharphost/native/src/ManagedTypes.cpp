#include <sharphost/ManagedTypes.h>

namespace sharphost
{
	Assembly AssemblyContextMetadata::findAssembly(const std::string& name) const
	{
		auto assemblyIter = m_assemblies.find(name);
		if (assemblyIter == m_assemblies.end())
			return {};

		auto [asmName, assembly] = *assemblyIter;
		return assembly;
	}

	std::vector<Assembly> AssemblyContextMetadata::getAssemblies() const
	{
		std::vector<Assembly> assemblies(m_assemblies.size());
		for (const auto& [key, assembly] : m_assemblies)
			assemblies.push_back(assembly);

		return std::move(assemblies);
	}

	std::vector<std::string> AssemblyContextMetadata::getAssemblyNames() const
	{
		std::vector<std::string> assemblyNames(m_assemblies.size());
		for (const auto& [key, assembly] : m_assemblies)
			assemblyNames.push_back(key);

		return std::move(assemblyNames);
	}

	void AssemblyContextMetadata::addAssembly(Assembly assembly)
	{
		m_assemblies.emplace(assembly.metadata.assemblyName, assembly);
	}

	void AssemblyContextMetadata::removeAssembly(Assembly& assembly)
	{
		m_assemblies.erase(assembly.metadata.assemblyName);
	}

	void AssemblyContextMetadata::resetMetadata()
	{
		m_assemblies.clear();
	}
} // namespace sharphost