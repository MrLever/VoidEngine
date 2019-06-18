//STD Headers
#include <memory>

//Library Headers
#include "glad/glad.h"

//Coati Headers
#include "Renderer.h"
#include "WindowManager.h"

namespace EngineCore {

	Renderer::Renderer(std::shared_ptr<WindowManager> window) : Window(std::move(window)){
		this->Window = Window;

	}


	Renderer::~Renderer() {
	}

	//Private Member Functions



	//Public Member Functions

	void Renderer::Render() {
		glClearColor(0.8f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Window->SwapBuffers();
	}
}