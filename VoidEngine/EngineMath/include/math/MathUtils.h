#pragma once

// Forward declarations of common math types to allow conversions
namespace math {

	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Quaternion;
	struct Rotator;

	extern constexpr double PI = 3.14159265358979323846;

	extern constexpr float DEFUALT_FLOAT_EPSILON = 0.005f;

	extern constexpr float ToRadians(float theta) {
		return (theta * (float)PI / 180.0f);
	}

	extern constexpr float ToDegrees(float theta) {
		return (theta * 180.0f / (float)PI);
	}

}