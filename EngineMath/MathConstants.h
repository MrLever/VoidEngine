#pragma once
//STD Headers
#include <cmath>

//Library Headers

//Void Engine Headers 

namespace math {
	static const double PI = 3.14159265358979323846;
	
	constexpr float ToRadians(float theta) {
		return (theta * (float)PI / 180.0f);
	}
}