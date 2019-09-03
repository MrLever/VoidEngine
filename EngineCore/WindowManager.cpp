//STD Headers
#include <iostream>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "WindowManager.h"


namespace EngineCore {
	WindowManager* WindowManager::CurrWindowManager = nullptr;
	
	const KeyboardInput WindowManager::ToggleFullscreenInput(
		KeyboardButton::ENTER, 
		ButtonState::PRESSED, 
		InputModifier::CTRL
	);

	WindowManager::WindowManager(const std::string& gameName, int windowWidth, int windowHeight) 
		: GameName(std::move(gameName)), IsFullscreen(false) {
		
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

	void WindowManager::MousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
		CurrWindowManager->PlayerInterface->ReportMouseInput(xPos, yPos);
	}


	void WindowManager::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
		CurrWindowManager->PlayerInterface->ReportMouseInput(yOffset);
	}

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
		glfwSetScrollCallback(Window.get(), MouseScrollCallback);

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

	void WindowManager::ToggleFullscreen() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		const int RESTORE_WIDTH = 640;
		const int RESTORE_HEIGHT = 480;
		if (!IsFullscreen) {
			WindowWidth = mode->width;
			WindowHeight = mode->height;

			glfwSetWindowMonitor(
				Window.get(), 
				glfwGetPrimaryMonitor(), 
				0, 0, WindowWidth, WindowHeight, 
				GLFW_DONT_CARE
			);

			IsFullscreen = true;
		}
		else {
			glfwSetWindowMonitor(
				Window.get(), 
				NULL, mode->width / 2, mode->height / 2, 
				RESTORE_WIDTH, RESTORE_HEIGHT, 
				GLFW_DONT_CARE
			);
			IsFullscreen = false;
		}

	}

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

	void WindowManager::DeleteWindow(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}

	void WindowManager::ReportWindowError(int error, const char* description) {
		std::cerr << "Error: " << description << std::endl;
	}

	void WindowManager::ResizeFrameBuffer(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);

		CurrWindowManager->WindowWidth = width;
		CurrWindowManager->WindowHeight = height;
	}

	void WindowManager::KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//Get time stamp for KeyBoardInput
		auto timeStamp = EngineUtils::GetGameTime();

		//Create Input wrapper object
		KeyboardInput input(
			static_cast<KeyboardButton>(key),
			static_cast<ButtonState>(action),
			mods,
			timeStamp
		);

		if (input == ToggleFullscreenInput) {
			CurrWindowManager->ToggleFullscreen();
		}
		else {
			//Report Input to Input Interface for later polling.
			CurrWindowManager->PlayerInterface->ReportKeyboardInput(input);
		}
	}

	void WindowManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		//Get time stamp for MouseButton event
		auto timeStamp = EngineUtils::GetGameTime();

		//Create Coati MouseInput
		MouseInput input(
			static_cast<MouseButton>(button),
			static_cast<ButtonState>(action),
			0,
			timeStamp
		);

		//Report input to InputInterface
		CurrWindowManager->PlayerInterface->ReportMouseInput(input);
	}

}