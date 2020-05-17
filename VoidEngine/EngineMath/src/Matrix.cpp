#include "math/GenVector.h"
#include "..\include\math\Matrix.h"

math::Matrix4x4::Matrix4x4() : Row1(Vector4()), Row2(Vector4()), Row3(Vector4()), Row4(Vector4()) {

}

math::Matrix4x4::Matrix4x4(const Vector4& Row1) : Row1(Row1), Row2(Vector4()), Row3(Vector4()), Row4(Vector4()) {

}

math::Matrix4x4::Matrix4x4(const Vector4& Row1, const Vector4& Row2) : Row1(Row1), Row2(Row2), Row3(Vector4()), Row4(Vector4()) {

}

math::Matrix4x4::Matrix4x4(const Vector4& Row1, const Vector4& Row2, const Vector4& Row3) : Row1(Row1), Row2(Row2), Row3(Row3), Row4(Vector4()) {

}

math::Matrix4x4::Matrix4x4(const Vector4& Row1, const Vector4& Row2, const Vector4& Row3, const Vector4& Row4) : Row1(Row1), Row2(Row2), Row3(Row3), Row4(Row4) {

}

math::Vector4 math::Matrix4x4::VectorMultiply(math::Vector4 vect) {
	return Vector4(vect.Dot(Row1), vect.Dot(Row2), vect.Dot(Row3), vect.Dot(Row4));
};

math::Matrix4x4& math::Matrix4x4::Transpose(){

	Vector4 NewRow1 = Vector4(Row1.X, Row2.X, Row3.X, Row4.X);
	Vector4 NewRow2 = Vector4(Row1.Y, Row2.Y, Row3.Y, Row4.Y);
	Vector4 NewRow3 = Vector4(Row1.Z, Row2.Z, Row3.Z, Row4.Z);
	Vector4 NewRow4 = Vector4(Row1.W, Row2.W, Row3.W, Row4.W);

	Row1 = NewRow1;
	Row2 = NewRow2;
	Row3 = NewRow3;
	Row4 = NewRow4;

	return *this;
}

math::Matrix4x4 math::Matrix4x4::Transpose(const Matrix4x4& matrix) {
	Matrix4x4 retval(matrix);
	return retval.Transpose();
}

math::Matrix4x4 math::Matrix4x4::MatrixMultiply(math::Matrix4x4 other)
{
	Vector4 R1 = Vector4(Row1.X * other.Row1.X + Row1.Y * other.Row2.X + Row1.Z * other.Row3.X + Row1.W * other.Row4.X,
		Row1.X * other.Row1.Y + Row1.Y * other.Row2.Y + Row1.Z * other.Row3.Y + Row1.W * other.Row4.Y,
		Row1.X * other.Row1.Z + Row1.Y * other.Row2.Z + Row1.Z * other.Row3.Z + Row1.W * other.Row4.Z,
		Row1.X * other.Row1.W + Row1.Y * other.Row2.W + Row1.Z * other.Row3.W + Row1.W * other.Row4.W);
	Vector4 R2 = Vector4(Row2.X * other.Row1.X + Row2.Y * other.Row2.X + Row2.Z * other.Row3.X + Row2.W * other.Row4.X,
		Row2.X * other.Row1.Y + Row2.Y * other.Row2.Y + Row2.Z * other.Row3.Y + Row2.W * other.Row4.Y,
		Row2.X * other.Row1.Z + Row2.Y * other.Row2.Z + Row2.Z * other.Row3.Z + Row2.W * other.Row4.Z,
		Row2.X * other.Row1.W + Row2.Y * other.Row2.W + Row2.Z * other.Row3.W + Row2.W * other.Row4.W);
	Vector4 R3 = Vector4(Row3.X * other.Row1.X + Row3.Y * other.Row2.X + Row3.Z * other.Row3.X + Row3.W * other.Row4.X,
		Row3.X * other.Row1.Y + Row3.Y * other.Row2.Y * Row3.Z + other.Row3.Y + Row3.W * other.Row4.Y,
		Row3.X * other.Row1.Z + Row3.Y * other.Row2.Z * Row3.Z + other.Row3.Z + Row3.W * other.Row4.Z,
		Row3.X * other.Row1.W + Row3.Y * other.Row3.W * Row2.Z + other.Row3.W + Row3.W * other.Row4.W);
	Vector4 R4 = Vector4(Row4.X * other.Row1.X + Row4.Y * other.Row2.X + Row4.Z * other.Row3.X + Row4.W * other.Row4.X,
		Row4.X * other.Row1.Y + Row4.Y * other.Row2.Y + Row4.Z * other.Row3.Y + Row4.W * other.Row4.Y,
		Row4.X * other.Row1.Z + Row4.Y * other.Row2.Z + Row4.Z * other.Row3.Z + Row4.W * other.Row4.Z,
		Row4.X * other.Row1.W + Row4.Y * other.Row2.W + Row4.Z * other.Row3.W + Row4.W * other.Row4.W);

	return Matrix4x4(R1, R2, R3, R4);
}
//Start Matrix3x3 Code
math::Matrix3x3::Matrix3x3() : Row1(Vector3()), Row2(Vector3()), Row3(Vector3()){

}

math::Matrix3x3::Matrix3x3(const Vector3& Row1) : Row1(Row1), Row2(Vector3()), Row3(Vector4()){

}

math::Matrix3x3::Matrix3x3(const Vector3& Row1, const Vector3& Row2) : Row1(Row1), Row2(Row2), Row3(Vector3()) {

}

math::Matrix3x3::Matrix3x3(const Vector3& Row1, const Vector3& Row2, const Vector3& Row3) : Row1(Row1), Row2(Row2), Row3(Row3) {

}

math::Vector3 math::Matrix3x3::VectorMultiply(math::Vector3 vect) {
	return Vector3(vect.Dot(Row1), vect.Dot(Row2), vect.Dot(Row3));
};

math::Matrix3x3& math::Matrix3x3::Transpose() {

	Vector3 NewRow1 = Vector3(Row1.X, Row2.X, Row3.X);
	Vector3 NewRow2 = Vector3(Row1.Y, Row2.Y, Row3.Y);
	Vector3 NewRow3 = Vector3(Row1.Z, Row2.Z, Row3.Z);

	Row1 = NewRow1;
	Row2 = NewRow2;
	Row3 = NewRow3;

	return *this;
}

math::Matrix3x3 math::Matrix3x3::Transpose(const Matrix3x3& matrix) {
	Matrix3x3 retval(matrix);
	return retval.Transpose();
}

math::Matrix3x3 math::Matrix3x3::MatrixMultiply(math::Matrix3x3 other)
{
	Vector3 R1 = Vector3(Row1.X * other.Row1.X + Row1.Y * other.Row2.X + Row1.Z * other.Row3.X,
		Row1.X * other.Row1.Y + Row1.Y * other.Row2.Y + Row1.Z * other.Row3.Y,
		Row1.X * other.Row1.Z + Row1.Y * other.Row2.Z + Row1.Z * other.Row3.Z);
	Vector3 R2 = Vector3(Row2.X * other.Row1.X + Row2.Y * other.Row2.X + Row2.Z * other.Row3.X,
		Row2.X * other.Row1.Y + Row2.Y * other.Row2.Y + Row2.Z * other.Row3.Y,
		Row2.X * other.Row1.Z + Row2.Y * other.Row2.Z + Row2.Z * other.Row3.Z);
	Vector3 R3 = Vector3(Row3.X * other.Row1.X + Row3.Y * other.Row2.X + Row3.Z * other.Row3.X,
		Row3.X * other.Row1.Y + Row3.Y * other.Row2.Y + Row3.Z * other.Row3.Y,
		Row3.X * other.Row1.Z + Row3.Y * other.Row2.Z + Row3.Z * other.Row3.Z);


	return Matrix3x3(R1, R2, R3);
}
//Start Matrix2x2 code
math::Matrix2x2::Matrix2x2() : Row1(Vector2()), Row2(Vector2()) {

}

math::Matrix2x2::Matrix2x2(const Vector2& Row1) : Row1(Row1), Row2(Vector2()) {

}

math::Matrix2x2::Matrix2x2(const Vector2& Row1, const Vector2& Row2) : Row1(Row1), Row2(Row2) {

}

math::Vector2 math::Matrix2x2::VectorMultiply(math::Vector2 vect) {
	return Vector2(vect.Dot(Row1), vect.Dot(Row2));
};

math::Matrix2x2& math::Matrix2x2::Transpose() {

	Vector2 NewRow1 = Vector2(Row1.X, Row2.X);
	Vector2 NewRow2 = Vector2(Row1.Y, Row2.Y);

	Row1 = NewRow1;
	Row2 = NewRow2;

	return *this;
}

math::Matrix2x2 math::Matrix2x2::Transpose(const Matrix2x2& matrix) {
	Matrix2x2 retval(matrix);
	return retval.Transpose();
}

math::Matrix2x2 math::Matrix2x2::MatrixMultiply(math::Matrix2x2 other)
{
	Vector2 R1 = Vector2(Row1.X * other.Row1.X + Row1.Y * other.Row2.X,
		Row1.X * other.Row1.Y + Row1.Y * other.Row2.Y);
	Vector2 R2 = Vector2(Row2.X * other.Row1.X + Row2.Y * other.Row2.X,
		Row2.X * other.Row1.Y + Row2.Y * other.Row2.Y);

	return Matrix2x2(R1, R2);
}
