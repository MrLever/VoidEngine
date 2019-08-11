#include "Vector3D.h"
#include <cmath>

using namespace EngineMath::Vector3D {

	Vector3D::Vector3D() {
		xy = Vector2D();
		z = 0;
	}

	Vector3D::Vector3D(T nx, T ny, T nz) {
		xy = Vector2D(nx, ny);
		z = nz;
	}

	Vector3D::Vector3D(Vector2D nv, T nz) {
		xy = nv;
		z = nz;
	}

	Vector3D Vector3D::sum(Vector3D b) {
		Vector3D sum = Vector3D(this.xy.sum(b.xy), this.z + b.z);
		return sum;
	}

	Vector3D Vector3D::subtract(Vector3D b) {
		Vector3D sum = Vector3D(this.xy.subtract(b.xy), this.z - b.z);
		return sum;
	}

	Vector3D Vector3D::scalar(T c) {
		Vector3D scalared = Vector3D((this.xy.scalar(c), this.z * c);
		return scalared;
	}

	Vector3D Vector3D::dot(Vector3D b) {
		return this.xy.dot(b.xy) + this.z * b.z;
	}

	Vector3D Vector3D::length() {
		return sqrt(pow(this.xy.length(), 2) + pow(this.z, 2));
	}

	static Vector3D Vector3D::interpolate3D(T xa, T ya, T za, T xb, T yb, T zb) {
		Vector3D interpolated = Vector3D(xb - xa, yb - ya, zb - za);
		return interpolated;
	}

	Vector3D Vector3D::project(Vector3D b) {
		return b.scalar(a.dot(b) / b.dot(b));
	}
}