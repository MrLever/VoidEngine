#pragma once
//STD Headers
#include <span>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/Type.h"

namespace utils {
	//Forward declarations
	struct Type;
	struct Property;
	struct Function;
	struct Class;

	/**
	 * Interface used by class type descriptors to access cached reflection data
	 */
	struct ClassDataInterface {
		virtual std::span<Property> Properties() = 0;
		virtual std::span<Function> Functions() = 0;
	};

	/**
	 * Data adapter for caching class type descriptor properties with use of dynamic allocation
	 * @tparam NumProperties the number of properties the class has.
	 * @tparam NumFunctions the number of member functions the class has.
	 */
	template<size_t NumProperties, size_t NumFunctions>
	struct ClassData : public ClassDataInterface {
		std::array<Property, NumProperties> m_Properties;
		std::array<Function, NumFunctions> m_Functions;

		ClassData(std::array<Property, NumProperties>& props, std::array<Function, NumFunctions>& funcs)
			: m_Properties(props), m_Functions(funcs) {
			
		}

		std::span<Property> Properties() final {
			return m_Properties;
		}

		std::span<Function> Functions() final {
			return m_Functions;
		}
	};

	struct Class : public Type {
		ClassDataInterface& m_Data;

		template<typename T>
		void SetProperty(void* instance, const utils::Name& name, const T& value);

		template<typename T>
		std::optional<T> GetProperty(const void* instance, const utils::Name& name) const;
	};

	template <typename T>
	void Class::SetProperty(void* instance, const utils::Name& name, const T& value) {
		for (auto& property : m_Data.Properties()) {
			if (property.m_Name == name) {
				property.Set(instance, value);
				break;
			}
		}
	}

	template<typename T>
	std::optional<T> Class::GetProperty(const void* instance, const utils::Name& name) const {
		for (auto& property : m_Data.Properties()) {
			if (property.m_Name == name) {
				return property.Get<T>(instance);
			}
		}

		return {};
	}
}