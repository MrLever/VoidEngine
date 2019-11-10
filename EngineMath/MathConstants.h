#pragma once
//STD Headers
#include <cmath>

//Library Headers

//Void Engine Headers 

namespace math {
	static constexpr double PI = 3.14159265358979323846;
	
	static constexpr float ToRadians(float theta) {
		return (theta * (float)PI / 180.0f);
	}

	static constexpr float ToDegrees(float theta) {
		return (theta * 180.0f / (float)PI);
	}
}