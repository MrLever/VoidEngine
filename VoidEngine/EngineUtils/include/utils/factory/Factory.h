#pragma once
//STD Headers
#include <any>
#include <concepts>
#include <typeinfo>
#include <memory>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/Logger.h"
#include "utils/TypeUtils.h"

namespace utils {

	/**
	 * @class FactoryBase
	 * @brief FactoryBase provides the functionality 
	 */
	template <class Base>
	class FactoryBase {
	public:
		/**
		 * Trivial destructor
		 */
		virtual ~FactoryBase() = default;

		/**
		 * Used to retrieve stringified name of the class a concrete factory produces
		 */
		virtual utils::Name GetProductName() const = 0;

		/**
		 * Instructs generic factory to find and use concrete factory to product product instance
		 * @param product The name of the product class
		 */
		template<class... Args>
		static Base* Create(const utils::Name& product, Args&&... args);

	protected:
		/**
		 * Finds a concrete factory that produces the specified product
		 * @param product The type name of the product class
		 */
		static const FactoryBase* const FindFactory(const utils::Name& product);

		/**
		 * Adds a concrete factory to the static list of factories
		 * @param factory The factory to register
		 */
		static void RegisterConcreteFactory(const FactoryBase& factory);

		/**
		 * Remove a concrete factory from the static list of factories
		 */
		static void UnregisterConcreteFactory(const FactoryBase& factory);

		/**
		 * Function to instruct factory to create an instance of the product class
		 */
		virtual Base* ConstructProxy() const = 0;

	private:
		/** Function to access map of product names to factories */
		static std::unordered_map<utils::Name, const FactoryBase*>& ConcreteFactories();
	};

	template<class Derived, class Base>
	//requires std::derived_from<Derived, Base>
	class Factory final : public FactoryBase<Base> {
	public:
		/**
		 * Constructor
		 */
		Factory();

		/**
		 * Destructor
		 */
		~Factory() override;

		/**
		 * Factories are not copy/move constructable
		 */
		Factory(const Factory& other) = delete;
		Factory(const Factory&& other) = delete;

		/**
		 * Factories are not copy/move assignable
		 */
		Factory& operator= (const Factory& other) = delete;
		Factory& operator= (const Factory&& other) = delete;

		/**
		 * Used to retrieve stringified name of the class this concrete factory produces
		 */
		utils::Name GetProductName() const override;

		/**
		 * Creates and returns a pointer to a new Derived product
		 */
		Derived* ConstructProxy() const override;

	private:
		/** Stringified name of class this factory produces */
		utils::Name ProductName;
	};

    /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////// FACTORY BASE IMPL /////////////////////////////// 
	/////////////////////////////////////////////////////////////////////////////////
	template<class Base>
	inline std::unordered_map<utils::Name, const FactoryBase<Base>*>& FactoryBase<Base>::ConcreteFactories() {
		static std::unordered_map<utils::Name, const FactoryBase<Base>*> factoryMap;
		return factoryMap;
	}

	template<class Base>
	template<class... Args>
	inline Base* FactoryBase<Base>::Create(const utils::Name& product, Args&& ...args) {
		auto factory = FindFactory(product);
		if (factory == nullptr) {
			utils::Logger::LogWarning("No concrete factory available to produce product " + product.StringID);
			return nullptr;
		}

		auto entity = factory->ConstructProxy();
		if (entity == nullptr) {
			utils::Logger::LogWarning(
				"Entity type " +
				product.StringID +
				" was not constructed properly."
			);
		}

		return entity;
	}

	template<class Base>
	inline const FactoryBase<Base>* const FactoryBase<Base>::FindFactory(const utils::Name& product) {
		auto factoryIter = ConcreteFactories().find(product);

		return (factoryIter == ConcreteFactories().end()) ? nullptr : factoryIter->second;
	}

	template<class Base>
	inline void FactoryBase<Base>::RegisterConcreteFactory(const FactoryBase& factory) {
		ConcreteFactories().emplace(factory.GetProductName(), &factory);
	}

	template<class Base>
	inline void FactoryBase<Base>::UnregisterConcreteFactory(const FactoryBase& factory) {
		ConcreteFactories().erase(factory.GetProductName());
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////// CONCRETE FACTORY IMPL /////////////////////////////// 
	/////////////////////////////////////////////////////////////////////////////////////
	template<class Derived, class Base>
	inline Factory<Derived, Base>::Factory() : ProductName(Derived::GetStaticTypename()) {
		FactoryBase<Base>::RegisterConcreteFactory(*this);
	}

	template<class Derived, class Base>
	inline Factory<Derived, Base>::~Factory() {
		FactoryBase<Base>::UnregisterConcreteFactory(*this);
	}

	template<class Derived, class Base>
	inline utils::Name Factory<Derived, Base>::GetProductName() const {
		return ProductName;
	}

	template<class Derived, class Base>
	inline Derived* Factory<Derived, Base>::ConstructProxy() const {
		return new Derived();
	}

}

#define ENABLE_FACTORY(DERIVED, BASE) \
	utils::Factory<DERIVED, BASE> DERIVED ## Factory;    
