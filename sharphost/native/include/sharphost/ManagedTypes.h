#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace sharphost
{
	struct Class;

	struct ReflectionMetadata
	{
		std::string name;
		std::string nameSpace;
		std::string assemblyName;
		std::string fullName;

		bool isPublic{};
		bool isPrivate{};
		bool isInternal{};
		bool isAbstract{};
		bool isSealed{};
		bool isStatic{};

		std::string objectType;
	};

	struct Attribute
	{
		ReflectionMetadata metadata{};

		std::vector<std::string>                     constructorArguments;
		std::unordered_map<std::string, std::string> namedArguments;
	};

	struct Parameter
	{
		std::string name;

		std::string paramType;
		std::string defaultValue;

		bool isOptional{};
		bool isByRef{};
		bool isIn{};
		bool isOut{};

		std::vector<Attribute> attributes;
	};

	struct Constructor
	{
		ReflectionMetadata metadata{};

		std::vector<Parameter> parameters;
		std::vector<Attribute> attributes;
	};

	struct Function
	{
		ReflectionMetadata metadata{};

		std::string returnType;

		std::vector<Parameter>   parameters;
		std::vector<Attribute>   attributes;
		std::vector<std::string> genericArguments;

		bool isStatic{};
		bool isAsync{};
		bool isVirtual{};
		bool isAbstract{};
		bool isOverride{};
		bool isGeneric{};
	};

	struct Field
	{
		ReflectionMetadata metadata{};

		std::vector<Attribute> attributes;

		std::string fieldType;

		bool isStatic{};
		bool isConst{};
	};

	struct Property
	{
		ReflectionMetadata metadata{};

		std::vector<Attribute> attributes;

		std::string propertyType;

		bool canRead{};
		bool canWrite{};
		bool isStatic{};
	};

	struct Enumerator
	{
		std::string member;
		std::string value;
	};

	struct Enum
	{
		ReflectionMetadata      metadata{};
		std::vector<Enumerator> enumerators;
	};

	struct Struct
	{
		ReflectionMetadata metadata{};

		std::string baseType;

		std::vector<std::string> interfaces;
		std::vector<Constructor> constructors;

		std::vector<Attribute> attributes;

		std::vector<Class>    classes;
		std::vector<Field>    fields;
		std::vector<Property> properties;
		std::vector<Struct>   structs;
		std::vector<Function> functions;
		std::vector<Enum>     enums;
	};

	struct Class
	{
		ReflectionMetadata metadata{};

		std::string baseType;

		std::vector<std::string> interfaces;
		std::vector<Constructor> constructors;

		std::vector<Attribute> attributes;
		std::vector<Function>  functions;
		std::vector<Field>     fields;
		std::vector<Property>  properties;
		std::vector<Enum>      enums;
		std::vector<Struct>    structs;
		std::vector<Class>     classes;
	};

	struct Assembly
	{
		ReflectionMetadata metadata{};

		std::vector<Class>  classes;
		std::vector<Struct> structs;
		std::vector<Enum>   enums;
	};

	class AssemblyContext;

	class AssemblyContextMetadata
	{
	public:
		[[nodiscard]] Assembly findAssembly(const std::string& name) const;

		[[nodiscard]] std::vector<Assembly>    getAssemblies() const;
		[[nodiscard]] std::vector<std::string> getAssemblyNames() const;

	protected:
		friend class AssemblyContext;

		void addAssembly(Assembly assembly);
		void removeAssembly(Assembly& assembly);

		void resetMetadata();

	private:
		std::unordered_map<std::string, Assembly> m_assemblies;
	};
} // namespace sharphost