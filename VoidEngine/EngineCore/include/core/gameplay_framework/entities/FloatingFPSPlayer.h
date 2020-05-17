#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/entities/Observer.h"

namespace core {

	class FloatingFPSPlayer : public Observer {
		ENABLE_RTTI(FloatingFPSPlayer)
	public:
		/**
		 * Constructor
		 */
		FloatingFPSPlayer();

		/**
		 * Destructor
		 */
		~FloatingFPSPlayer() override;

		/**
		 * Extend basic floater controls to allow shooting
		 */
		virtual void SetupInputComponent(InputComponent* component) override;


	};
}

