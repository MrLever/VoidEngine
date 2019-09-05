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
		std::shared_ptr<WindowManager> window, EngineInterfacePtr engineInterface, const EngineUtils::ResourceHandle& configuration) 
		: Configurable(configuration), VoidEngineInterface(std::move(engineInterface)),
		  Window(std::move(window)) {

	}

	Renderer::~Renderer() {

	}

	void Renderer::Render(std::vector<std::shared_ptr<Entity>> scene) {
		glClearColor(0.24f, 0.28f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (const auto& entity : scene) {
			//entity->Draw();

			////Bind bind the entity's vertex buffer
			//glBindBuffer(GL_ARRAY_BUFFER, drawable.VBO);
			//glBufferData(
			//	GL_ARRAY_BUFFER, 
			//	sizeof(drawable.Vertices.data()), 
			//	drawable.Vertices.data(), 
			//	GL_STREAM_DRAW
			//);
		}

		Window->SwapBuffers();
	}

	void Renderer::Configure() {
		//TODO (MrLever): Leverage configuration settings
	}

}