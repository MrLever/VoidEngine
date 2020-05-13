#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "utils/configuration/Configurable.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"
#include "utils/resource/ResourceHandle.h"

namespace core {

	class AudioManager : public utils::Configurable {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param engineInterface Shared pointer to the engine utility interface this system will use
		 * @param configFile The file location of the configuration file this system will use
		 */
		AudioManager(ThreadPoolPtr threadPool, const utils::ResourceHandle<utils::Configuration>& configuration);
		
		/**
		 * Destructor
		 */
		~AudioManager() = default;

		/**
		 * Configures the object using the settings in the config file
		 */
		void Configure() override;

	private:
		/** The game's active thread pool */
		ThreadPoolPtr m_ThreadPool;
	};

}