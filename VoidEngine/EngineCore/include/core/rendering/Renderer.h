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

	class Renderer : public utils::Configurable, public EventBusNode {
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(
			EventBus* bus,
			std::shared_ptr<RenderingContext> renderingAPI,
			const utils::ResourceHandle<utils::Configuration>& configuration
		);

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
		void Render(Level* scene);

		/**
		 * Applies Renderer Configuration Settings
		 */
		void Configure() override;

	private:

		void HandleWindowResize(WindowResizedEvent* event);

		std::shared_ptr<RenderingContext> RenderingAPI;

		/** The defualt view matrix to use if a scene does not provide one */
		glm::mat4 DefualtViewMatrix;

		/** The default projection matrix to use if a scene does not provide one */
		glm::mat4 DefaultProjectionMatrix;
	};

	static void OpenGLDebugCallback(
		GLenum source, GLenum type,
		GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam
	);
}