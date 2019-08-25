#pragma once
//STD Headers

//Library Headers

//Math Headers
#include "Vector.h"

namespace EngineMath {

	//Public CTORS
	Vector::Vector() {
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = 0;
	}

	Vector::Vector(Ts... args) {
		data = new T[size];
		data = {args...};
	}

	//Public Methods

	Vector::Dot(const Vector& other) {
		if (size != other.size)
			//ERROR
		else {
			auto sum = data[0] * other.data[0];
			for (int i = 1; i < size; i++)
				sum += data[i] * other.data[i];

			return sum;
		}
	}

	Vector::Project(const Vector & other) {
			return other * (this.Dot(other) / other.Dot(other));
	}

	//Operator Overloads

	Vector& operator+(const Vector& other) {
		if (other.size != size) {
			//error or something?
		}
		else {
			for (int i = 0; i < size; i++)
				data[i] += other->data[i];

			return *this;
		}
	}

	Vector& operator-(const Vector& other) {
		if (other.size != size) {
			//error or something?
		}
		else {
			for (int i = 0; i < size; i++)
				data[i] -= other->data[i];

			return *this;
		}
	}

	Vector& operator*(const T& scalar) {
		for (int i = 0; i < size; i++)
			data[i] = data[i] * scalar;
		return *this;
	}

	Vector& operator*(const Vector& other) {
		if (size != other.size && size != 3)
			//ERROR
		else {
			auto ax = data[1] * other.data[2] - data[2] * other.data[1];
			auto ay = data[2] * other.data[0] - data[0] * other.data[2];
			auto az = data[0] * other.data[1] - data[1] * other.data[0];
			return Vector(ax, ay, az);
		}
	}
}