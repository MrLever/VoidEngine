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
		AudioManager(EngineInterfacePtr engineInterface, const std::string& configFile);
		~AudioManager() = default;


		void Configure() override;

	private:
		/** Interface the Audio Manager uses to access Engine Utility classes */
		std::shared_ptr<EngineInterface> VoidEngineInterface;
	};

}