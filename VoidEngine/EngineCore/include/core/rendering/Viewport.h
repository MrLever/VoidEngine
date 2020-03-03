#pragma once
//STD Headers

//Library Headers

//Void Engine Headers

namespace core {

	struct Viewport {
		int X, Y;
		int Width, Height;

		Viewport() : X(0), Y(0), Width(0), Height(0) {

		}

		Viewport(int x, int y, int width, int height)
			: X(x), Y(y), Width(width), Height(height) {

		}
	};
}