#pragma once
//STD Headers
#include <concepts>
#include <typeinfo>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Name.h"
#include "Logger.h"

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
		 * Function to instruct factory to create an instance of the product class
		 */
		virtual Base* Create() const = 0;

		/**
		 * Instructs generic factory to find and use concrete factory to product product instance
		 * @param product The name of the product class
		 */
		Base* Create(const std::string& product) const;

		/**
		 * Instructs generic factory to find and use concrete factory to product product instance
		 * @param product The name of the product class
		 */
		Base* Create(const utils::Name& product) const;

	protected:
		/**
		 * Finds a concrete factory that produces the specified product
		 * @param product The type name of the product class
		 */
		const FactoryBase* const FindFactory(const utils::Name& product) const;

		/**
		 * Adds a concrete factory to the static list of factories
		 * @param factory The factory to register
		 */
		static void RegisterConcreteFactory(const FactoryBase& factory);

		/**
		 * Remove a concrete factory from the static list of factories
		 */
		static void UnregisterConcreteFactory(const FactoryBase& factory);

	private:
		/** Map of product names to factories */
		static std::unordered_map<utils::Name, const FactoryBase*> ConcreteFactories;
	};

	template<class Base>
	std::unordered_map<utils::Name, const FactoryBase<Base>*> FactoryBase<Base>::ConcreteFactories;

	template<class Base>
	inline Base* FactoryBase<Base>::Create(const std::string& product) const {
		return Create(utils::Name(product));
	}

	template<class Base>
	inline Base* FactoryBase<Base>::Create(const utils::Name& product) const {
		auto factory = FindFactory(product);
		if (factory == nullptr) {
			utils::Logger::LogWarning("No concrete factory available to produce product " + product.StringID);
		}

		return factory->Create();
	}

	template<class Base>
	inline const FactoryBase<Base>* const FactoryBase<Base>::FindFactory(const utils::Name& product) const {
		auto factoryIter = ConcreteFactories.find(product);

		return (factoryIter == ConcreteFactories.end()) ? nullptr : factoryIter->second;
	}


	template<class Base>
	inline void FactoryBase<Base>::RegisterConcreteFactory(const FactoryBase& factory) {
		ConcreteFactories.emplace(factory.GetProductName(), &factory);
	}

	template<class Base>
	inline void FactoryBase<Base>::UnregisterConcreteFactory(const FactoryBase& factory) {
		ConcreteFactories.erase(factory.GetProductName());
	}

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
		Derived* Create() const override;

	private:
		/** Stringified name of class this factory produces */
		utils::Name ProductName;
	};

	template<class Derived, class Base>
	inline Factory<Derived, Base>::Factory() : ProductName(typeid(Derived).name()) {
		RegisterConcreteFactory(*this);
	}

	template<class Derived, class Base>
	inline Factory<Derived, Base>::~Factory() {
		UnregisterConcreteFactory(*this);
	}

	template<class Derived, class Base>
	inline utils::Name Factory<Derived, Base>::GetProductName() const {
		return utils::Name(typeid(Derived).name());
	}

	template<class Derived, class Base>
	inline Derived* Factory<Derived, Base>::Create() const {
		return new Derived();
	}

}

