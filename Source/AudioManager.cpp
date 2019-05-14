//STD Headers
#include <iostream>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "AudioManager.h"

namespace EngineCore {

	AudioManager::AudioManager(std::shared_ptr<MessageBus> GameMessageBus) : MessageBusNode(GameMessageBus) {
		PublishMessage("Audio Manager Initialized", MessageType::Initialization);
		this->RegisterReciever();
	}

	void AudioManager::RegisterEvents() {
	}

	void AudioManager::ReceiveMessage(Message message) {
		std::cout << "Audio Manager Message Recieved: \n";
		std::cout << "\t" << message.GetEvent() << "\n";
	}

}