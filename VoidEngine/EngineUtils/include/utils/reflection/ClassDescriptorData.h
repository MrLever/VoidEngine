#pragma once
//STD Headers
#include <span>
#include <optional>

//Library Headers

//Void Engine Headers

namespace utils {
	//Forward declarations
	struct ClassDescriptor;
	struct Property;
	struct Function;

	/**
	 * @struct ClassDataInterfaces
	 * @brief Interface used by class type descriptors to access cached reflection data
	 */
	struct ClassDescriptorData {
		/**
		 * @return Span of properties for only the owning class descriptor (no-inheritance)
		 */
		virtual std::span<Property> GetProperties() = 0;

		/**
		 * @return Count of properties for only the owning class descriptor (no-inheritance)
		 */
		virtual std::size_t GetPropertyCount() const = 0;

		/**
		 * @return Span of functions for only the owning class descriptor (no-inheritance)
		 */
		virtual std::span<Function> GetFunctions() = 0;

		/**
		 * @return Count of functions for only the owning class descriptor (no-inheritance)
		 */
		virtual std::size_t GetFunctionCount() const = 0;

		/**
		 * @return Span of direct parent class descriptors for the owning class descriptor
		 */
		virtual std::span<const ClassDescriptor*> GetParents() = 0;

		/**
		 * @return Count of direct parent class descriptors for the owning class descriptor
		 */
		virtual std::size_t GetParentCount() const = 0;
	};

	/**
	 * Data adapter for caching class type descriptor properties with use of dynamic allocation
	 * @tparam NumProperties the number of properties the class has.
	 * @tparam NumFunctions the number of member functions the class has.
	 */
	template<size_t NumProperties, size_t NumFunctions, size_t NumParents = 0>
	struct ClassData : public ClassDescriptorData {
		/**
		 * Constructor
		 * @param props The properties stored in this data cache
		 * @param funcs The functions stored in this data cache
		 */
		ClassData(
			std::array<Property, NumProperties> props,
			std::array<Function, NumFunctions> funcs
		);

		/**
		 * Constructor
		 * @param props The properties stored in this data cache
		 * @param funcs The functions stored in this data cache
		 * @param parents The ClassDescriptors for ALL parents of this class
		 */
		ClassData(
			std::array<Property, NumProperties> props,
			std::array<Function, NumFunctions> funcs,
			std::array<const ClassDescriptor*, NumParents> parents
		);

		/**
		 * @return A non-owning immutable reference to the property requested
		 */
		const Property* const GetProperty(const utils::Name& propName);


		std::span<Property> GetProperties() override final { return m_Properties; }
		std::size_t GetPropertyCount() const override final { return NumProperties; }

		std::span<Function> GetFunctions() override final { return m_Functions; }
		std::size_t GetFunctionCount() const override final { return NumFunctions; }
		
		std::span<const ClassDescriptor*> GetParents() override final { return m_Parents; }
		std::size_t GetParentCount() const override final { return NumParents; }

	private:
		/** Array of properties registered for the owning ClassDescriptor */
		std::array<Property, NumProperties> m_Properties;

		/** Array of functions registered for the owning ClassDescriptor */
		std::array<Function, NumFunctions> m_Functions;

		/** Array of parents registered for the owning ClassDescriptor */
		std::array<const ClassDescriptor*, NumParents> m_Parents;
	};

	template<size_t NumProperties, size_t NumFunctions, size_t NumParents>
	inline ClassData<NumProperties, NumFunctions, NumParents>::ClassData(
		std::array<Property, NumProperties> props,
		std::array<Function, NumFunctions> funcs
	) : m_Properties(props), m_Functions(funcs), m_Parents() {

	}

	template<size_t NumProperties, size_t NumFunctions, size_t NumParents>
	inline ClassData<NumProperties, NumFunctions, NumParents>::ClassData(
		std::array<Property, NumProperties> props, 
		std::array<Function, NumFunctions> funcs,
		std::array<const ClassDescriptor*, NumParents> parents
	) : m_Properties(props), m_Functions(funcs), m_Parents(parents) {

	}

	template<size_t NumProperties, size_t NumFunctions, size_t NumParents>
	inline const Property* const ClassData<NumProperties, NumFunctions, NumParents>::GetProperty(
		const utils::Name& propName
	) {

		for (auto& prop : m_Properties) {
			if (propName == prop.m_name) {
				return &prop;
			}
		}

		return nullptr;
	}
}