//STD Headers
#include <iostream>
#include <utility>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "AudioManager.h"

namespace EngineCore {

	AudioManager::AudioManager(EngineInterfacePtr engineInterface, EngineUtils::ResourceHandle configuration) 
		: Configurable(configuration), VoidEngineInterface(std::move(engineInterface)) {
		
	}

	void AudioManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}