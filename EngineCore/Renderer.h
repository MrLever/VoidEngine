#pragma once
//STD Headers
#include <memory>

//Library Headers
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "CameraComponent.h"
#include "Configurable.h"
#include "Level.h"
#include "ThreadPool.h"
#include "ResourceManager.h"

namespace core {

	//Forward Class declarations
	class WindowManager;

	class Renderer : public utils::Configurable{
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(
			std::shared_ptr<WindowManager> window,
			ThreadPoolPtr threadPool,
			const utils::ResourceHandle<utils::Configuration>& configuration
		);

		/**
		 * Destructor
		 */
		~Renderer();

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
		/** The game's active thread pool */
		ThreadPoolPtr GameThreadPool;

		/** Shared with the Input System, the render can draw to this window. */
		std::shared_ptr<WindowManager> Window;

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