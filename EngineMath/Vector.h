#pragma once
//STD Headers

//Library Headers

//Math Headers

namespace EngineMath {
	template <typename T>
	class Vector2 {
	public:
		T X;
		T Y;

		//tors
		Vector2() : X(0), Y(0) {

		}

		Vector2(T x) : X(x), Y(0) {

		}

		Vector2(T x, T y) : X(x), Y(y) {

		}

		//operator overloads
		virtual bool operator== (const Vector2& other) const {
			return this->X == other.X && this->Y == other.Y;
		}
	};

	template <typename T>
	class Vector3 {
	public:
		T X;
		T Y;
		T Z;

		//tors
		Vector3() : X(0), Y(0), Z(0) {

		}

		Vector3(T x) : X(x), Y(0), Z(0) {

		}

		Vector3(T x, T y) : X(x), Y(y), Z(0) {

		}
		
		Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {
		
		}

		
		auto Dot(const Vector3<T> &other) -> decltype(other.X) {
			return (X * other.X) + (Y * other.Y) + (Z + other.Z);
		}

		//operator overloads
		virtual bool operator== (const Vector3& other) {
			return 
				this->X == other.X 
				&& this->Y == other.Y
				&& this->Z == other.Z;
		}
	};
}