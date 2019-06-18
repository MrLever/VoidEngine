//STD Headers
#include <iostream>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "WindowManager.h"


namespace EngineCore {
	WindowManager* WindowManager::CurrWindowManager = nullptr;

	WindowManager::WindowManager(std::string gameName, int windowWidth, int windowHeight) 
		: GameName(std::move(gameName)) {
		
		WindowWidth = windowWidth;
		WindowHeight = windowHeight;

		InitGLFW();
		InitGLAD();

		PlayerInterface = std::make_shared<InputInterfaceManager>();

		CurrWindowManager = this;
	}


	WindowManager::~WindowManager() {
		glfwTerminate();
	}


	//Private Member Functions

	void WindowManager::InitGLFW() {
		if (glfwInit() == GLFW_FALSE) {
			// Initialization failed
			return;
		}

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		Window = std::shared_ptr<GLFWwindow>(
			glfwCreateWindow(WindowWidth, WindowHeight, GameName.c_str(), nullptr, nullptr),
			DeleteWindow
		);

		if (Window == nullptr) {
			glfwSetWindowShouldClose(Window.get(), GLFW_TRUE);
		}

		glfwMakeContextCurrent(Window.get());
		
		//Setup callbacks
		glfwSetFramebufferSizeCallback(Window.get(), ResizeFrameBuffer);
		glfwSetKeyCallback(Window.get(), KeyboardInputCallback);
		glfwSetMouseButtonCallback(Window.get(), MouseButtonCallback);
		glfwSetCursorPosCallback(Window.get(), MousePositionCallback);

		glfwSetWindowUserPointer(Window.get(), this);
	}

	void WindowManager::InitGLAD() {
		auto GLADaddress = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
		bool success = gladLoadGLLoader(GLADaddress) == 0;
		if (success) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			std::terminate();
		}

		glViewport(0, 0, WindowWidth, WindowHeight);
	}

	//Public Member Functions

	std::shared_ptr<GLFWwindow> WindowManager::getWindow() {
		return Window;
	}

	void WindowManager::SwapBuffers() {
		glfwSwapBuffers(Window.get());
		glfwPollEvents();
	}

	bool WindowManager::WindowTerminated() {
		return (glfwWindowShouldClose(Window.get()) == GLFW_TRUE);
	}

	std::shared_ptr<InputInterfaceManager> WindowManager::GetInputInterface() {
		return PlayerInterface;
	}

}