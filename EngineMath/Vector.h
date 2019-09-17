#pragma once
//STD Headers

//Library Headers

//Math Headers

namespace EngineMath {
	struct Vector2 {
		float X;
		float Y;

		/**
		 * Defualt Constructor
		 */
		Vector2() : X(0), Y(0) {

		}

		/**
		 * Constructor 
		 * @param x The vector's X value
		 */
		Vector2(float x) : X(x), Y(0) {

		}

		/**
		 * Constructor
		 * @param x The vector's X value
		 * @param y The vector's Y value
		 */
		Vector2(float x, float y) : X(x), Y(y) {

		}

		//operator overloads
		virtual bool operator== (const Vector2& other) const {
			return this->X == other.X && this->Y == other.Y;
		}
	};

	struct Vector3 {
		float X;
		float Y;
		float Z;

		//tors
		Vector3() : X(0), Y(0), Z(0) {

		}

		Vector3(float x) : X(x), Y(0), Z(0) {

		}

		Vector3(float x, float y) : X(x), Y(y), Z(0) {

		}
		
		Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {
		
		}

		float Dot(const Vector3 &other) {
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

	struct Vector4 {
		float X;
		float& R = X;

		float Y;
		float& G = Y;

		float Z;
		float& B = Z;

		float W;
		float& A = W;
	};

	using Color = Vector4;
}