#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/Type.h"

namespace utils {
	//Forward declarations
	struct Type;
	struct Property;
	struct Function;

	struct Class : public Type {
		std::vector<Property> m_Properties;
		std::vector<Function> m_Functions;

		template<typename T>
		void SetProperty(void* instance, const utils::Name& name, const T& value);

		template<typename T>
		std::optional<T> GetProperty(const void* instance, const utils::Name& name) const;
	};

	template <typename T>
	void Class::SetProperty(void* instance, const utils::Name& name, const T& value) {
		for (auto& property : m_Properties) {
			if (property.m_Name == name) {
				property.Set(instance, value);
				break;
			}
		}
	}

	template<typename T>
	std::optional<T> Class::GetProperty(const void* instance, const utils::Name& name) const {
		for (auto& property : m_Properties) {
			if (property.m_Name == name) {
				return property.Get<T>(instance);
			}
		}

		return {};
	}
}