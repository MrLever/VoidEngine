#pragma once
#include "Vector2D.h"

namespace EngineMath {

	template <typename T>

	class Vector3D {
		public Vector2D xy;
		public T z;

	public:
		Vector3D();
		Vector3D(T nx, T ny, T nz);
		Vector3D(Vector2D nv, T nz);
		Vector3D sum(Vector3D b);
		Vector3D subtract(Vector3D b);
		Vector3D scalar(T c);
		Vector3D dot(Vector3D b);
		Vector3D cross(Vector3D b);
		Vector3D length();
		static Vector3D interpolate3D(T xa, T ya, T za, T xb, T yb, T zb);
		Vector3D project(Vector3D b);
	};