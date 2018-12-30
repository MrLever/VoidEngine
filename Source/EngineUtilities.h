#pragma once

//STD Headers
#include <string>


//Library Headers

namespace EngineUtilities {
	static unsigned int FNV1aHash(std::string input) {

		int FNV_prime = 1099511628211;

		int hash = 14695981039346656037;

		for (int i = 0; i < input.length(); i++) {

			hash = hash xor (int)input[i];
			hash = hash * FNV_prime;
		}

		return hash;

	}
}

