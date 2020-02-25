#pragma once

//STD Headers
#include <string>
#include <chrono>


//Library Headers
#include "utils/Logger.h"

namespace utils {

	constexpr uint32_t FNV1aSeed = 0x811c9dc5;

	/**
	 * When possible, this function is evaluated at compile time.
	 */
	inline constexpr uint32_t FNV1aHash(const char* input, const uint32_t value = FNV1aSeed) noexcept {
		const uint32_t prime = 0x1000193;
		
		if (input[0] == '\0') {
			return value;
		}
		else {
			return FNV1aHash(&input[1], (value ^ input[0]) * prime);
		}

	}

	#ifdef VE_ENABLE_ASSERTS
		#define VE_ASSERT(x, ...) { if(!(x)) { utils::Logger::LogError("Assertion Failed: {0} + __VA_ARGS__"); __debugbreak(); } }
	#else
		#define VE_ASSERT(x, ...)
	#endif
}

