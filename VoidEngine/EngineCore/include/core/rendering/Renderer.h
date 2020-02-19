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

#include "core/Level.h"
#include "core/event_system/EventBusNode.h"
#include "core/event_system/events/WindowResizedEvent.h"
#include "core/rendering/RenderingContext.h"
#include "core/rendering/components/CameraComponent.h"

namespace core {

	//Forward Class declarations
	class Window;

	enum class RendererAPI {
		NONE = 0,
		OPENGL,
		DIRECT3D12
	};

	class Renderer : public EventBusNode {
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(EventBus* bus,	std::shared_ptr<RenderingContext> renderingAPI);

		/**
		 * Destructor
		 */
		~Renderer();

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		void ReceiveEvent(Event* event) override;

		/**
		 * Allows EventBus to query the node's subscription, and filter events accordingly
		 */
		unsigned GetSubscription() override;

		/** 
		 * Draws to the sceen
		 * @param scene The scene to draw
		 */
		void Render(std::vector<Entity*> entiti);

		/**
		 * Sets up camera render data properly
		 * @param camera The camera to configure
		 */
		void InitializeCamera(CameraComponent* camera) const;

		/**
		 * Notifies the renderer to use a different camera for drawing
		 * @param camera The camera to render from
		 */
		void UseCamera(CameraComponent* camera);

		/**
		 * Allows rendering to query the active rendering API
		 * to construct the correct abstractions
		 * @return The active rendering API
		 */
		static RendererAPI GetRendererAPI();

	private:

		void HandleWindowResize(WindowResizedEvent* event);

		CameraComponent* ActiveCamera;

		std::shared_ptr<RenderingContext> DeviceContext;

		/** The default view matrix to use if a scene does not provide one */
		glm::mat4 DefualtViewMatrix;

		/** The default projection matrix to use if a scene does not provide one */
		glm::mat4 DefaultProjectionMatrix;

		static RendererAPI API;
	};

}