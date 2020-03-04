#pragma once
//STD Headers
#include <memory>

//Library Headers
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "utils/configuration/Configurable.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"

#include "core/rendering/Viewport.h"
#include "core/rendering/RenderDevice.h"
#include "core/rendering/LightingEnvironment.h"
#include "core/rendering/components/CameraComponent.h"
#include "core/rendering/components/GraphicsComponent.h"

namespace core {

	//Forward Class declarations
	class Window;

	enum class DrawMode {
		LINE,
		TRIANGLE,
	};

	class Renderer {
	public:

		/**
		 * Initializes renderer systems
		 */
		static void Initialize(Viewport viewport);

		/**
		 * Reports window resize to renderer
		 */
		static void HandleWindowResize(Viewport newViewport);

		/**
		 * Collects enviornment data (lights, camera, etc) from scene used to 
		 * affect all draw calls until EndFrame()
		 * @param activeCamera The camera to be used in rendering the frame
		 * @param lighting The totality of the scene's lighting enviornment
		 */
		static void BeginFrame(CameraComponent* activeCamera, const LightingEnvironment* lighting);

		/**
		 * Resets enviornment data for rendering
		 */
		static void EndFrame();

		/**
		 * Submits an object for rendering
		 */
		static void Submit(
			std::shared_ptr<ShaderProgram> shader,
			std::shared_ptr<VertexArray> vao,
			const glm::mat4& model,
			DrawMode drawMode = DrawMode::TRIANGLE
		);

		/**
		 * Allows rendering to query the active rendering API
		 * to construct the correct abstractions
		 * @return The active rendering API
		 */
		static RenderDevice::API GetRendererAPI();

	private:
		/** Read-only pointer to Camera being used to modify incomming draw calls */
		static CameraComponent* s_ActiveCamera;

		/** Read-only pointer to light scene being used to modify incomming draw calls */
		static const LightingEnvironment* s_LightingEnvironment;
		
		/** Viewport used to define renderable area */
		static Viewport s_ActiveViewport;

		/** The default view matrix to use if a scene does not provide one */
		static glm::mat4 s_DefualtViewMatrix;

		/** The default projection matrix to use if a scene does not provide one */
		static glm::mat4 s_DefaultProjectionMatrix;

	};

}