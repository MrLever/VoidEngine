//STD Headers
#include <utility>

//Library Headers

//Coati Headers
#include "audio/AudioManager.h"

namespace core {

	AudioManager::AudioManager(
			ThreadPoolPtr threadPool, const utils::ResourceHandle<utils::Configuration>& configuration
		) : Configurable(configuration), m_ThreadPool(std::move(threadPool)) {
		
	}

	void AudioManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}