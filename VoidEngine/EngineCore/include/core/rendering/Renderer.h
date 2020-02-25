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
#include "core/rendering/RenderDevice.h"
#include "core/rendering/components/CameraComponent.h"
#include "core/rendering/components/GraphicsComponent.h"

namespace core {

	//Forward Class declarations
	class Window;

	class Renderer : public EventBusNode {
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(EventBus* bus,	std::shared_ptr<RenderDevice> renderingAPI);

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
		 * Collects enviornment data (lights, camera, etc) from scene used to affect all draw calls
		 */
		void InitializeEnvironment(Scene* scene);

		/**
		 * Discards enviornment data for rendering
		 */
		void ClearEnvironment();

		/**
		 * Submits an object for rendering
		 */
		void Submit(GraphicsComponent* drawData);

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
		static RenderDevice::API GetRendererAPI();

	private:

		void HandleWindowResize(WindowResizedEvent* event);

		CameraComponent* ActiveCamera;

		std::shared_ptr<RenderDevice> m_RenderingAPI;

		/** The default view matrix to use if a scene does not provide one */
		glm::mat4 m_DefualtViewMatrix;

		/** The default projection matrix to use if a scene does not provide one */
		glm::mat4 m_DefaultProjectionMatrix;
	};

}