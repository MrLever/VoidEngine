#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/RenderDevice.h"

namespace core {

	class OpenGLRenderDevice : public RenderDevice  {
	public:
		/**
		 * Constructor
		 */
		OpenGLRenderDevice();

		/**
		 * Used to set the rendering engine's viewport
		 */
		void SetViewport(RenderDevice::Viewport viewport) override;
		
		/**
		 * Used to clear drawing buffer
		 */
		void Clear() override;

		/**
		 * Set's buffer clear color
		 */
		virtual void SetClearColor(math::Vector4 color) override;

	};

	static void OpenGLDebugCallback(
		GLenum source, GLenum type,
		GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam
	);
}