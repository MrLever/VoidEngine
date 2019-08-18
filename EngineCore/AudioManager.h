#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "Configurable.h"
#include "EngineInterface.h"
#include "MessageBusNode.h"

namespace EngineCore {

	class AudioManager : public EngineUtils::Configurable {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param engineInterface Shared pointer to the engine utility interface this system will use
		 * @param configFile The file location of the configuration file this system will use
		 */
		AudioManager(EngineInterfacePtr engineInterface, const std::string& configFile);
		
		/**
		 * Destructor
		 */
		~AudioManager() = default;

		/**
		 * Configures the object using the settings in the config file
		 */
		void Configure() override;

	private:
		/** Interface the Audio Manager uses to access Engine Utility classes */
		std::shared_ptr<EngineInterface> VoidEngineInterface;
	};

}