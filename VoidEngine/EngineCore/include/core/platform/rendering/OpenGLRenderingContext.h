#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/RenderingContext.h"

namespace core {

	class OpenGLRenderingContext : public RenderingContext  {
	public:
		/**
		 * Constructor
		 */
		OpenGLRenderingContext();

		/**
		 * Used to set the rendering engine's viewport
		 */
		void SetViewport(RenderingContext::Viewport viewport) override;

	};

	static void OpenGLDebugCallback(
		GLenum source, GLenum type,
		GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam
	);
}