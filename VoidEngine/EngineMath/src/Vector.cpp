#pragma once
//STD Headers
#include <limits>

//Library Headers

//Math Headers
#include "math/Vector.h"

namespace math {
	Vector2::Vector2() : X(0), Y(0) {

	}

	Vector2::Vector2(float x) : X(x), Y(0) {

	}

	Vector2::Vector2(float x, float y) : X(x), Y(y) {

	}

	float Vector2::Dot(const Vector2& other) const {
		return (X * other.X) + (Y * other.Y);
	}

	bool Vector2::operator== (const Vector2& other) const {
		return this->X == other.X && this->Y == other.Y;
	}

	Vector2 operator+ (const Vector2& lhs, const Vector2& rhs){
		return Vector2(lhs.X + rhs.X, lhs.Y + rhs.Y);
	}

	Vector2 operator- (const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.X - rhs.X, lhs.Y - rhs.Y);
	}

	Vector2 operator* (const Vector2& lhs, float rhs) {
		return Vector2(lhs.X * rhs, lhs.Y * rhs);
	}

	Vector2 operator*(float lhs, const Vector2& rhs) {
		return rhs * lhs;
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(
			lhs.X + rhs.X,
			lhs.Y + rhs.Y,
			lhs.Z + rhs.Z
		);
	}

	Vector3& Vector3::operator+=(const Vector3& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;

		return *this;
	}

	Vector3 Vector3::operator- () {
		return Vector3(-X, -Y, -Z);
	}

	Vector3& Vector3::operator*=(float rhs) {
		X *= rhs;
		Y *= rhs;
		Z *= rhs;

		return *this;
	}

	Vector3& Vector3::operator/=(float rhs) {
		X /= rhs;
		Y /= rhs;
		Z /= rhs;
		
		return *this;
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(
			lhs.X - rhs.X,
			lhs.Y - rhs.Y,
			lhs.Z - rhs.Z
		);
	}

	Vector3 operator* (const Vector3& lhs, float rhs) {
		return Vector3(
			lhs.X * rhs, 
			lhs.Y * rhs, 
			lhs.Z * rhs
		);
	}

	Vector3 operator*(float lhs, const Vector3& rhs) {
		return rhs * lhs;
	}

	Vector3 operator/(const Vector3& lhs, float rhs) {
		return Vector3(
			lhs.X / rhs,
			lhs.Y / rhs,
			lhs.Z / rhs
		);
	}

	Vector3 operator/(float lhs, const Vector3& rhs) {
		return rhs/lhs;
	}

	std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
		return out << "[" << vec.X << ", " << vec.Y << ", " << vec.Z << "]";
	}

	Vector3::Vector3() : X(0), Y(0), Z(0) {

	}

	Vector3::Vector3(float x) : X(x), Y(0), Z(0) {

	}

	Vector3::Vector3(float x, float y) : X(x), Y(y), Z(0) {

	}

	Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {

	}

	float Vector3::Dot(const Vector3& other) const{
		return (X * other.X) + (Y * other.Y) + (Z + other.Z);
	}

	Vector3 Vector3::Cross(const Vector3& other) const {
		return 
			Vector3(
				(Y * other.Z) - (Z * other.Y),
				(Z * other.X) - (X * other.Z),
				(X * other.Y) - (Y * other.X)
			);
	}

	float Vector3::Magnitude() const {
		return 
			std::sqrt(
				(X * X) + (Y * Y) + (Z * Z)
			);
	}

	float Vector3::Magnitude2() const {
		return (X * X) + (Y * Y) + (Z * Z);
	}

	Vector3 Vector3::Normalize() const {
		auto mag = Magnitude();
		return Vector3(X / mag, Y / mag, Z / mag);
	}

	bool Vector3::operator== (const Vector3& other) const {
		constexpr float EPSILON = std::numeric_limits<float>::epsilon() * 100;
		return
			std::abs(this->X - other.X) < EPSILON
			&& std::abs(this->Y - other.Y) < EPSILON
			&& std::abs(this->Z - other.Z) < EPSILON;
	}

	Vector4::Vector4() {
		X = Y = Z = W = 0;

	}

	Vector4::Vector4(float x) : X(x) {
		Y = Z = W = 0;
	}

	Vector4::Vector4(float x, float y) 
		: X(x), Y(y) {

		Z = W = 0;
	}

	Vector4::Vector4(float x, float y, float z) : X(x), Y(y), Z(z), W(0) {

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w) {

	}

}