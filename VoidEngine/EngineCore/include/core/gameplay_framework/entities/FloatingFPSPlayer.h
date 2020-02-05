#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/entities/DefaultPlayerEntity.h"

namespace core {

	class FloatingFPSPlayer : public DefaultPlayerEntity {
		TYPE_INFO_DECL(FloatingFPSPlayer)
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

