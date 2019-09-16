#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "Configurable.h"
#include "ThreadPool.h"
#include "ResourceManager.h"

namespace EngineCore {

	//Forward Class declarations
	class WindowManager;

	class Renderer : public EngineUtils::Configurable{
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(
			std::shared_ptr<WindowManager> window,
			ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager,
			const EngineUtils::ResourceHandle& configuration
		);

		/**
		 * Destructor
		 */
		~Renderer();

		/** 
		 * Draws to the sceen
		 * @param scene The scene to draw
		 */
		void Render(std::vector<GraphicsComponent*> components);

		/**
		 * Applies Renderer Configuration Settings
		 */
		void Configure() override;

	private:
		/** The game's active thread pool */
		ThreadPoolPtr GameThreadPool;

		/** The game's active resource manager */
		ResourceManagerPtr GameResourceManager;

		/** Shared with the Input System, the render can draw to this window. */
		std::shared_ptr<WindowManager> Window;
	};

	static void OpenGLDebugCallback(
		GLenum source, GLenum type,
		GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam
	);
}