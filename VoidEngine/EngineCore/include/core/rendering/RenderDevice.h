#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "math/Vector.h"
#include "core/rendering/VertexArray.h"
#include "core/rendering/Viewport.h"

namespace core {

	/**
	 * Virtual interface used to abstract rendering APIs
	 */
	class RenderDevice {
	public:

		enum class API {
			NONE = 0,
			OPENGL,
			DIRECT3D12
		};

		/**
		 * Returns a pointer to a RenderDevice
		 */
		static std::unique_ptr<RenderDevice> Create();

		/**
		 * Initializes render device.
		 * @note Renderer must be initialized AFTER window creation.
		 */
		virtual void Initialize() = 0;

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
		Viewport GetViewport() const;
			   
		/**
		 * Used to clear drawing buffer
		 */
		virtual void Clear() = 0;

		/**
		 * Set's buffer clear color
		 */
		virtual void SetClearColor(math::Vector4 color) = 0;

		/**
		 * Allows a draw call to be sent to the system's rendering device
		 */
		virtual void DrawIndexed(std::shared_ptr<VertexArray> vao) = 0;

		/**
		 * Allows a draw call to be sent to the system's rendering device
		 */
		virtual void DrawWireframe(std::shared_ptr<VertexArray> vao) = 0;

		/**
		 * Allows rendering to query the active rendering API
		 * to construct the correct abstractions
		 * @return The active rendering API
		 */
		static RenderDevice::API GetRendererAPI();

	protected:
		Viewport CurrentViewport;

		static API s_API;
	};

}