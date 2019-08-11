#include "Vector2D.h"
#include <cmath>
using namespace EngineMath::Vector2D {

	Vector2D::Vector2D() {
		x = 0;
		y = 0;
	}

	Vector2D::Vector2D(T nx, T ny) {
		x = nx;
		y = ny;
	}

	Vector2D Vector2D::sum(Vector2D b) {
		Vector2D sum = Vector2D();
		sum.x = this.x + b.x;
		sum.y = this.y + b.y;
		return sum;
	}

	Vector2D Vector2D::subtract(Vector2D b) {
		Vector2D sum = Vector2D();
		sum.x = this.x - b.x;
		sum.y = this.y - b.y;
		return sum;
	}

	Vector2D Vector2D::scalar(T c) {
		Vector2D scalared = Vector2D(this.x * c, this.y * c);
		return scalared;
	}

	Vector2D Vector2D::dot(Vector2D b) {
		return this.x * b.x + this.y * b.y;
	}

	Vector2D Vector2D::length() {
		return sqrt(pow(this.x, 2) + pow(this.y, 2));
	}

	static Vector2D Vector2D::interpolate2D(T xa, T xb, T ya, T yb) {
		Vector2D interpolated = Vector2D(xb - xa, yb - ya);
		return interpolated;
	}

	Vector2D Vector2D::project(Vector2D b) {
		return b.scalar(a.dot(b) / b.dot(b));
	}
}