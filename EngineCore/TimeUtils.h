#pragma once

//STD Headers
#include <chrono>
#include <string>

//Library Headers

namespace utils {
	using GameTime = unsigned long long;

	/**
	 * Utility for getting the games current time.
	 * @return The game's current time since epoch
	 */
	GameTime GetGameTime();

	/**
	 * Returns the current time as a string
	 * @return The Machine's local time in a human-readable format
	 */
	std::string GetLocalTime();
}