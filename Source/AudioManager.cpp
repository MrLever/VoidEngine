#include "AudioManager.h"



AudioManager::AudioManager(std::shared_ptr<MessageBus> GameMessageBus) {
	this->GameMessageBus = GameMessageBus;
}


AudioManager::~AudioManager() {
}
