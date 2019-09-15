//STD Headers
#include <memory>

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "Entity.h"
#include "Renderer.h"
#include "WindowManager.h"

namespace EngineCore {

	Renderer::Renderer(
			std::shared_ptr<WindowManager> window, ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager, const EngineUtils::ResourceHandle& configuration
		) : Configurable(configuration), GameThreadPool(std::move(threadPool)), 
		  GameResourceManager(std::move(resourceManager)), Window(std::move(window)) {

	}

	Renderer::~Renderer() {

	}

	void Renderer::Render() {
		glClearColor(0.24f, 0.28f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Window->SwapBuffers();
	}

	void Renderer::Configure() {
		//TODO (MrLever): Leverage configuration settings
	}

}