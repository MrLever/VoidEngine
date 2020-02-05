#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Entity.h"

namespace core {

	/**
	 * @class StaticObserver
	 * @brief A Static Observer is a camera weilding entity that stands absolutely still
	 */
	class StaticObserver : public Entity {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(StaticObserver)
	
	public:
		/**
		 * Constructor
		 */
		StaticObserver();

		/**
		 * Allows an entity to configure itself after it is constructed
		 */
		virtual void Initialize();

		/**
         * Pure virtual function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		void BeginPlay() override;

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate();
	};

}
