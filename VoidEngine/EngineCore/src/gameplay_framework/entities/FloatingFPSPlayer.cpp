#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/entities/FloatingFPSPlayer.h"
#include "Scene.h"

namespace core {
	TYPE_INFO_IMPL(FloatingFPSPlayer)

	ENABLE_FACTORY(FloatingFPSPlayer, Entity)

	FloatingFPSPlayer::FloatingFPSPlayer() {

	}

	FloatingFPSPlayer::~FloatingFPSPlayer() {

	}

	void FloatingFPSPlayer::SetupInputComponent(InputComponent* component) {
		Observer::SetupInputComponent(component);

		component->BindAction(
			"Fire", 
			ActionType::PRESSED,
			[this](float deltaTime) {
				GetWorld()->SpawnEntity(utils::Name("Projectile"), this);
			}
		);

	}
}

