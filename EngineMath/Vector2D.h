#pragma once

namespace EngineMath {

	template <typename T>

	class Vector2D {
		public T x;
		public T y;

	public:
		Vector2D();
		Vector2D(T nx, T ny);
		Vector2D sum(Vector2D b);
		Vector2D subtract(Vector2D b);
		Vector2D scalar(T c);
		Vector2D dot(Vector2D b);
		Vector2D length();
		static Vector2D interpolate2D(T xa, T ya, T xb, T yb);
		Vector2D project(Vector2D b);
	};
}