#pragma once
//STD Headers
#include <span>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/TypeDescriptor.h"

namespace utils {
	//Forward declarations
	struct TypeDescriptor;
	struct Property;
	struct Function;

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
	template<size_t NumProperties, size_t NumFunctions, size_t NumParents = 0>
	struct ClassData : public ClassDataInterface {
		std::array<Property, NumProperties> m_Properties;
		std::array<Function, NumFunctions> m_Functions;

		/**
		 * Constructor
		 * @param props The properties stored in this data cache
		 * @param funcs The functions stored in this data cache
		 */
		ClassData(
			std::array<Property, NumProperties>& props, 
			std::array<Function, NumFunctions>& funcs
		);

		std::span<Property> Properties() final {
			return m_Properties;
		}

		std::span<Function> Functions() final {
			return m_Functions;
		}
	};

	struct ClassDescriptor : public TypeDescriptor {

		/**
		 * Constructor
		 * @param type This class's type descriptor
		 * @param data The reflection data of this classes properties and functions
		 */
		ClassDescriptor(const TypeDescriptor& type, ClassDataInterface& data) : TypeDescriptor(type), m_Data(data) {
		
		}

		template<typename T>
		void SetPropertyData(void* instance, const utils::Name& name, const T& value);

		template<typename T>
		[[nodiscard]] std::optional<T> GetPropertyData(
			const void* instance, 
			const utils::Name& name
		) const;

		size_t GetPropertyCount() const {
			return m_Data.Properties().size();
		}

	private:
		ClassDataInterface& m_Data;
	};

	////////////////////////////////////////////////////////////////////////////////
	// Class Type Descriptor impl
	////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	void ClassDescriptor::SetPropertyData(void* instance, const utils::Name& name, const T& value) {
		for (auto& property : m_Data.Properties()) {
			if (property.m_Name == name) {
				property.SetValue(instance, value);
				break;
			}
		}
	}

	template<typename T>
	[[nodiscard]] std::optional<T> ClassDescriptor::GetPropertyData(
		const void* instance, 
		const utils::Name& name
	) const {
		for (auto& property : m_Data.Properties()) {
			if (property.m_Name == name) {
				return property.GetValue<T>(instance);
			}
		}

		//Return invalid optional
		return {};
	}

	////////////////////////////////////////////////////////////////////////////////
	// Class data cache impl
	////////////////////////////////////////////////////////////////////////////////
	template<size_t NumProperties, size_t NumFunctions, size_t NumParents>
	inline ClassData<NumProperties, NumFunctions, NumParents>::ClassData(
		std::array<Property, NumProperties>& props, std::array<Function, NumFunctions>& funcs
	) : m_Properties(props), m_Functions(funcs) {

	}

}