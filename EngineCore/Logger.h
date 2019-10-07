#pragma once
#ifdef ERROR
	#undef ERROR
#endif //Error was being defined in wingdi 

//STD Headers
#include <string>
#include <iostream>
#include <sstream>

//Library Headers

//Void Engine Headers

namespace utils {
	enum class LogLevel {
		INFO,
		DEBUG,
		WARNING,
		ERROR
	};

	class Logger {
	public:
		static void LogInfo(const std::string& message);
		static void LogDebug(const std::string& message);
		static void LogWarning(const std::string& message);
		static void LogError(const std::string& message);
	};

}

