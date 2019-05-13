#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "InputInterface.h"
#include "EngineUtilities.h"


namespace EngineCore {

	class WindowManager {

	private:
		//Private class members
		std::shared_ptr<GLFWwindow> Window;
		std::string GameName;
		std::shared_ptr<InputInterface> PlayerInterface;

		static WindowManager* CurrWindowManager;

	public:
		//CTORS
		WindowManager(std::string GameName);
		~WindowManager();

	private:
		//Private member functions
		void InitGLFW();
		void InitGLAD();

	public:
		//Public member functions
		std::shared_ptr<GLFWwindow> getWindow();

		void SwapBuffers();
		bool WindowTerminated();

		std::shared_ptr<InputInterface> GetInputInterface();

		//Static Functions
		static void DeleteWindow(GLFWwindow* window) {
			glfwDestroyWindow(window);
		}

		static void ReportWindowError(int error, const char* description) {
			std::cerr << "Error: " << description << std::endl;
		}

		static void ResizeFrameBuffer(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		static void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			//Get time stamp for KeyBoardInput
			auto timeStamp = EngineUtilities::GetGameTime();

			//Create Coati KeyboardInput
			KeyboardInput input(static_cast<KeyType>(key), static_cast<ButtonState>(action), timeStamp);
			
			//Report Input to Input Interface for later polling.
			CurrWindowManager->PlayerInterface->ReportKeyboardInput(input);

		}

		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			//Get time stamp for MouseButton event
			auto timeStamp = EngineUtilities::GetGameTime();
			
			//Create Coati MouseInput
			MouseInput input(static_cast<MouseButton>(button), timeStamp);

			//Report input to InputInterface
			CurrWindowManager->PlayerInterface->ReportMouseKeyInput(input);
		}

		static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
			CurrWindowManager->PlayerInterface->ReportMousePosition(xPos, yPos);
		}
	};

}