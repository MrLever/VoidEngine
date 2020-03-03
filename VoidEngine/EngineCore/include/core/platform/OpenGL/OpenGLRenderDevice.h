#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/RenderDevice.h"

namespace core {

	class OpenGLRenderDevice : public RenderDevice  {
	public:
		
		/**
		 * Initializes render device.
		 */
		void Initialize() override;

		/**
		 * Used to set the rendering engine's viewport
		 */
		void SetViewport(Viewport viewport) override;
		
		/**
		 * Used to clear drawing buffer
		 */
		void Clear() override;

		/**
		 * Set's buffer clear color
		 */
		void SetClearColor(math::Vector4 color) override;

		void DrawIndexed(std::shared_ptr<VertexArray> vao) override;

		void DrawWireframe(std::shared_ptr<VertexArray> vao) override;

	};
}