#pragma once
//STD headers
#include <cmath>
#include <ostream>

//Math headers
#include "math/Vector.h"

namespace math {

	struct Matrix4x4 {

		Vector4 Row1;
		Vector4 Row2;
		Vector4 Row3;
		Vector4 Row4;


		Matrix4x4();
		
		Matrix4x4(const Vector4& Row1);

		Matrix4x4(const Vector4& Row1, const Vector4& Row2);

		Matrix4x4(const Vector4& Row1, const Vector4& Row2, const Vector4& Row3);
		
		Matrix4x4(const Vector4& Row1, const Vector4& Row2, const Vector4& Row3, const Vector4& Row4);

		Vector4 VectorMultiply(math::Vector4 vect);

		Matrix4x4& Transpose(); // In place transpose of matrix

		[[nodiscard]] static Matrix4x4 Transpose(const Matrix4x4& matrix);

		Matrix4x4 MatrixMultiply(math::Matrix4x4 other);


	};

	struct Matrix3x3 {

		Vector3 Row1;
		Vector3 Row2;
		Vector3 Row3;

		Matrix3x3();

		Matrix3x3(const Vector3& Row1);

		Matrix3x3(const Vector3& Row1, const Vector3& Row2);

		Matrix3x3(const Vector3& Row1, const Vector3& Row2, const Vector3& Row3);

		Vector3 VectorMultiply(math::Vector3 vect);

		Matrix3x3& Transpose(); // In place transpose of matrix

		[[nodiscard]] static Matrix3x3 Transpose(const Matrix3x3& matrix);

		Matrix3x3 MatrixMultiply(math::Matrix3x3 other);


	};

	struct Matrix2x2 {

		Vector2 Row1;
		Vector2 Row2;
		Vector2 Row3;

		Matrix2x2();

		Matrix2x2(const Vector2& Row1);

		Matrix2x2(const Vector2& Row1, const Vector2& Row2);

		Vector2 VectorMultiply(math::Vector2 vect);

		Matrix2x2& Transpose(); // In place transpose of matrix

		[[nodiscard]] static Matrix2x2 Transpose(const Matrix2x2& matrix);

		Matrix2x2 MatrixMultiply(math::Matrix2x2 other);


	};

}