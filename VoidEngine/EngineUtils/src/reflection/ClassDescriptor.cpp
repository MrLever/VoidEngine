//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/reflection/ClassDescriptor.h"
#include "utils/reflection/Property.h"
//#include "utils/reflection/Function.h"

namespace utils {

	std::vector<Property> ClassDescriptor::GetProperties() const {

		std::vector<Property> properties;

		//Scan parent classes and capture their properties
		for (auto& parent : m_Data->GetParents()) {
			auto parentProps = parent->GetProperties();
			for (auto& prop : parentProps) {
				properties.emplace_back(prop);
			}
		}

		//Add this ClassDescriptor's properties
		for (auto& prop : m_Data->GetProperties()) {
			properties.emplace_back(prop);
		}

		return properties;
	}

	std::optional<Property> ClassDescriptor::GetProperty(const utils::Name& propertyName) const {
		for (auto& property : GetProperties()) {
			if (property.m_Name == propertyName) {
				return property;
			}
		}
		return {};
	}
}