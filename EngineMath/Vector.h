#pragma once

#include "Vector3D.h"

namespace EngineMath {

	template <typename T>

	class Vector {
		public T x;
		public T y;
		public T z;
		public T w;

	public:
		Vector(T x, T y, T z, T w);
		Vector sum(Vector b);
		Vector subtract(Vector b);
		Vector scalar(T c);
		Vector dot(Vector b);
		static Vector interpolate(T xa, T ya, T za, T wa, T xb, T yb, T zb, T wb);
		Vector project(Vector b);
	}
}