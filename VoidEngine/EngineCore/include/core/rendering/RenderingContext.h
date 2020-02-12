#pragma once
//STD Headers

//Library Headers

//Void Engine Headers

namespace core {


	class RenderingContext {
	public:
		struct Viewport {
			int X, Y;
			int Width, Height;

			Viewport(int x, int y, int width, int height)
				: X(x), Y(y), Width(width), Height(height) {

			}
		};

		/**
		 * Constructor
		 */
		RenderingContext();

		/**
		 * Used to set the rendering engine's viewport
		 */
		virtual void SetViewport(int x, int y, int width, int height);

		/**
		 * Used to set the rendering engine's viewport
		 */
		virtual void SetViewport(Viewport viewport) = 0;

		/**
		 * Used to get viewport's current dimensions
		 */
		virtual Viewport GetViewport(int x, int y, int width, int height);
	
	private:
		Viewport CurrentViewport;
	};

}