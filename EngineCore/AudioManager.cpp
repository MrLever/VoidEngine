//STD Headers
#include <iostream>
#include <utility>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "AudioManager.h"

namespace core {

	AudioManager::AudioManager(
			ThreadPoolPtr threadPool, ResourceManagerPtr resourceManager, 
			utils::ResourceHandle configuration
		) : Configurable(configuration), GameThreadPool(std::move(threadPool)), 
		    GameResourceManager(std::move(resourceManager)) {
		
	}

	void AudioManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}