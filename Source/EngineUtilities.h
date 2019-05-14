#pragma once

//STD Headers
#include <string>
#include <chrono>


//Library Headers

namespace EngineUtilities {

	static unsigned FNV1aHash(std::string input) {

		const auto FNV_prime = 1099511628211;
		const auto hashSeed = 14695981039346656037;
		
		auto hash = hashSeed;
		
		for (auto &letter : input) {

			hash = hash ^ static_cast<unsigned>(letter);
			hash = hash * FNV_prime;
		}

		return static_cast<unsigned>(hash);

	}

	static double GetGameTime() {
		auto currentTime = std::chrono::high_resolution_clock::now();
		double timeStamp = std::chrono::duration<double>(currentTime.time_since_epoch()).count();
		
		return timeStamp;
	}
}

