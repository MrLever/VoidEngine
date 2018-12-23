//STD Headers
#include <iostream>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Message.h"
#include "AudioManager.h"




AudioManager::AudioManager(std::shared_ptr<MessageBus> GameMessageBus) : MessageBusNode(GameMessageBus) {
	this->GameMessageBus = GameMessageBus;
	Message initMessage("Audio Manager Initialized", Initialization);
	GameMessageBus.get()->PublishMessage(initMessage);
}


AudioManager::~AudioManager() {
}

void AudioManager::ReceiveMessage(Message message) {
	std::cout << "Audio Manager Message Recieved: \n";
	std::cout << "\t" << message.getEvent() << "\n";
}
