//STD Headers
#include <iostream>
#include <sstream>

//Library Headers

//Void Engine Headers
#include "Logger.h"
#include "TimeUtils.h"

namespace utils {
	void Logger::LogInfo(const std::string& message) {
		std::stringstream logMessage;
		
		auto time = utils::GetGameTime();
		logMessage << time << " INFO| " << message;
		
		std::cout << logMessage.str() << std::endl;
	}

	void Logger::LogDebug(const std::string& message) {
		std::stringstream logMessage;

		auto time = utils::GetGameTime();
		logMessage << time << " DEBUG| " << message;

		std::cout << logMessage.str() << std::endl;
	}

	void Logger::LogWarning(const std::string& message) {
		std::stringstream logMessage;

		auto time = utils::GetGameTime();
		logMessage << time << " WARNING| " << message;

		std::cout << logMessage.str() << std::endl;
	}

	void Logger::LogError(const std::string& message) {
		std::stringstream logMessage;

		auto time = utils::GetGameTime();
		logMessage << time << " ERROR| " << message;

		std::cout << logMessage.str() << std::endl;
	}
}