#pragma once
//STD Headers

//Library Headers

//Void Engine Headers

namespace core {

	class RenderingContext {
	public:
		/**
		 * Constructor
		 */
		RenderingContext();

		/**
		 * Used to set the rendering engine's viewport
		 */
		virtual void SetViewport(int x, int y, int width, int height) = 0;

	};

}