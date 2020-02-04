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

#include "CameraComponent.h"
#include "EventBusNode.h"
#include "Level.h"
#include "WindowResizedEvent.h"

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
			std::shared_ptr<Window> window,
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

		/** Shared with the Input System, the render can draw to this window. */
		std::shared_ptr<Window> GameWindow;

		/** The defualt view matrix to use if a scene does not provide one */
		glm::mat4 DefualtViewMatrix;

		/** The default projection matrix to use if a scene does not provide one */
		glm::mat4 DefaultProjectionMatrix;

		/** The Rendering context's width */
		int ContextWidth;

		/** The Rendering context's height */
		int ContexHeight;
	};

	static void OpenGLDebugCallback(
		GLenum source, GLenum type,
		GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam
	);
}