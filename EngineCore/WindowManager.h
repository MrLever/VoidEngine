#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "InputInterfaceManager.h"
#include "EngineUtilities.h"


namespace EngineCore {
	/**
	 * @class WindowManager
	 * @brief Object to manage the OS-specific window/input context.
	 */
	class WindowManager {

	public:
		/**
		 * Constructor
		 * @param gameName The name to display in the game's window title bar
		 * @param windowWidth The width of the game window
		 * @param windowHeight The height of the game window
		 */
		WindowManager(const std::string& gameName, int windowWidth, int windowHeight);
		
		/**
		 * Destructor
		 */
		~WindowManager();

		/**
		 * Function to access a pointer to the GLFW window
		 * @return Shared_Pointer the active GLFW window
		 */
		std::shared_ptr<GLFWwindow> getWindow();

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		void SwapBuffers();

		/**
		 * Function to query status of the managed window
		 * @return whether the window was terminated or not
		 */
		bool WindowTerminated();

		/**
		 * Provides caller access to the game's active Input Interfaces
		 * @return A shared pointer to the game's active input interface manager
		 */
		std::shared_ptr<InputInterfaceManager> GetInputInterface();

		
		/// NOTE: The following functions are static so that they can be used as callbacks from GLFW
		/**
		 * Properly deletes the window supplied to avoid memory leaks
		 */
		static void DeleteWindow(GLFWwindow* window) {
			glfwDestroyWindow(window);
		}

		/**
		 * Callback to display GLFW errors
		 */
		static void ReportWindowError(int error, const char* description) {
			std::cerr << "Error: " << description << std::endl;
		}

		/** 
		 * Callback to resize the window/draw frame buffer
		 */
		static void ResizeFrameBuffer(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			CurrWindowManager->WindowWidth = width;
			CurrWindowManager->WindowHeight = height;
		}

		/**
		 * Callback to capture keyboard input
		 */
		static void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			//Get time stamp for KeyBoardInput
			auto timeStamp = EngineUtils::GetGameTime();

			//Create Coati KeyboardInput
			KeyboardInputPtr input = std::make_shared<KeyboardInput>(
				static_cast<KeyboardButton>(key), 
				static_cast<ButtonState>(action), 
				timeStamp
			);
			
			//Report Input to Input Interface for later polling.
			CurrWindowManager->PlayerInterface->ReportKeyboardInput(input);

		}

		/**
		 * Callback to capture mouse button events
		 */
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			//Get time stamp for MouseButton event
			auto timeStamp = EngineUtils::GetGameTime();
			
			//Create Coati MouseInput
			MouseInputPtr input = std::make_shared<MouseInput>(
				static_cast<MouseButton>(button),
				static_cast<ButtonState>(action),
				timeStamp
			);

			//Report input to InputInterface
			CurrWindowManager->PlayerInterface->ReportMouseKeyInput(input);
		}

		/**
		 * Callback to capture deltas in mouse position
		 */
		static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
			CurrWindowManager->PlayerInterface->ReportMousePosition(xPos, yPos);
		}

	private:
		/** Performs initialization of the GLFW library */
		void InitGLFW();

		/** Performs initialization of the GLAD library */
		void InitGLAD();

		/** The game's window */
		std::shared_ptr<GLFWwindow> Window;
		
		/** The game's name */
		std::string GameName;

		/** The interface for all input devices */
		std::shared_ptr<InputInterfaceManager> PlayerInterface;

		/** The window's width */
		int WindowWidth;

		/** The window's height */
		int WindowHeight;

		/** Pointer to the active window manager to allow static callback functions to work properly */
		static WindowManager* CurrWindowManager;

		/** OpenGL Major version */
		static const int OPENGL_MAJOR = 4;

		/** OpenGL Minor version */
		static const int OPENGL_MINOR = 5;
	};

}