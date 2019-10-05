//STD Headers
#include <utility>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "AudioManager.h"

namespace core {

	AudioManager::AudioManager(
			ThreadPoolPtr threadPool, const utils::ResourceHandle<utils::Configuration>& configuration
		) : Configurable(configuration), GameThreadPool(std::move(threadPool)) {
		
	}

	void AudioManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}