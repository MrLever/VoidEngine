#pragma once
//STD Headers
#include <limits>

//Library Headers

//Math Headers
#include "math/MathConstants.h"
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
		return std::abs(X - other.X) < DEFUALT_FLOAT_EPSILON && 
			   std::abs(Y - other.Y) < DEFUALT_FLOAT_EPSILON;
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

	float Vector3::MagnitudeSqr() const {
		return (X * X) + (Y * Y) + (Z * Z);
	}

	Vector3& Vector3::Normalize() {
		auto mag = Magnitude();
		X /= mag;
		Y /= mag; 
		Z /= mag;

		return *this;
	}

	Vector3 Vector3::Normalize(const Vector3& vec) {
		return Vector3(vec).Normalize();
	}

	bool Vector3::operator== (const Vector3& other) const {
		return this->Equals(other, DEFUALT_FLOAT_EPSILON);
	}

	bool Vector3::Equals(const Vector3& other, float epsilon) const {
		return 
			std::abs(this->X - other.X) < epsilon &&
			std::abs(this->Y - other.Y) < epsilon &&
			std::abs(this->Z - other.Z) < epsilon;
	}

	Vector4::Vector4() {
		X = Y = Z = W = 0;

	}

	Vector4::Vector4(const Vector3& vec3) 
		: X(vec3.X), Y(vec3.Y), Z(vec3.Z), W(0) {

	}

	Vector4::Vector4(const Vector3& vec3, float w) 
		: X(vec3.X), Y(vec3.Y), Z(vec3.Z), W(w) {

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w) {

	}

}