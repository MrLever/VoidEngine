#pragma once

//STD Headers
#include <chrono>


//Library Headers

namespace EngineUtils {
	using GameTime = unsigned long long;

	/**
	 * Utility for getting the games current time.
	 * @return The game's current time since epoch
	 */
	GameTime GetGameTime();
}