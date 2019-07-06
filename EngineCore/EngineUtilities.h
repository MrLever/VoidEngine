#pragma once

//STD Headers
#include <string>
#include <chrono>


//Library Headers


namespace EngineCore {

	static unsigned long long FNV1aHash(const std::string &input) {

		const auto FNV_prime = 1099511628211;
		const auto hashSeed = 14695981039346656037;
		
		auto hash = hashSeed;
		
		for (auto &letter : input) {

			hash = hash ^ static_cast<unsigned>(letter);
			hash = hash * FNV_prime;
		}

		return static_cast<unsigned long long>(hash);

	}
}

