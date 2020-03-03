#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/RenderDevice.h"

namespace core {
	
	/**
	 * Represents a command from the Renderer to the RenderDevice
	 * Handles creation of render device at startup
	 */
	class RenderCommand {
	public:

		static void Initialize();

		static void SetViewport(Viewport viewport);

		static void SetClearColor(math::Vector4 color);
		
		static void Clear();

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vao);

		static void DrawWireframe(std::shared_ptr<VertexArray> vao);

	private:
		static std::unique_ptr<RenderDevice> s_RenderDevice;

	};

}