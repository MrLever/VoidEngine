#pragma once

//STD Headers
#include <string>
#include <chrono>


//Library Headers

namespace EngineUtilities {

	static unsigned FNV1aHash(std::string input) {

		auto FNV_prime = 1099511628211;

		auto hash = 14695981039346656037;

		for (int i = 0; i < input.length(); i++) {

			hash = hash ^ static_cast<unsigned>(input[i]);
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

