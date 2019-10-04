#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Void Engine Headers
#include "EngineUtilities.h"
#include "KeyboardInput.h"


namespace core {
	//Forward Class Declarations
	class InputManager;

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
		std::shared_ptr<GLFWwindow> GetWindow();

		/**
		 * Wrapper function to instruct GLFW to poll for window and input events
		 */
		void PollEvents();

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		void SwapBuffers();

		/**
		 * Attaches an input manager to this window to handle input callbacks
		 */
		void SetInputManager(std::shared_ptr<InputManager> inputManager);

		/**
		 * Function to query status of the managed window
		 * @return whether the window was terminated or not
		 */
		bool WindowTerminated();

		/**
		 * Instructs window to poll and report gamepad input
		 */
		void HandleGamepadInput();

		/// NOTE: The following functions are static so that they can be used as callbacks from GLFW
		/**
		 * Properly deletes the window supplied to avoid memory leaks
		 * @param window The GLFWwindow to destroy
		 */
		static void DeleteWindow(GLFWwindow* window);

		/**
		 * Callback to display GLFW errors
		 * @param error The error's numerical code
		 * @param description The Error's description
		 */
		static void ReportWindowError(int error, const char* description);

		/** 
		 * Callback to resize the window/draw frame buffer
		 * @param window The window to be resized
		 * @param width The new width to apply to the window
		 * @param height The new height to apply to the window
		 */
		static void ResizeFrameBuffer(GLFWwindow* window, int width, int height);

		/**
		 * Callback to capture keyboard input
		 * @param window The window reporting this input
		 * @param key The keyboard key being reported
		 * @param scancode The platform-specific key code for the key being pressed
		 * @param action The type of key action being reported
		 * @param mods A bitfield to specify if any modifying keys (shift, caps lock, etc) are being 
		 *             held in conjunction with this button
		 */
		static void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		 * Callback to capture mouse button events
		 * @param window The window reporting this input
		 * @param button The mouse being reported
		 * @param action The type of key action being reported
		 * @param mods A bitfield to specify if any modifying keys (shift, caps lock, etc) are being 
		 *             held in conjunction with this button
		 */
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		/**
		 * Callback to capture deltas in mouse position
		 * @param window The window reporting the change in mouse position
		 * @param xPos The X-coordinate of the cursor's new position
		 * @param yPos The Y-coordinate of the cursor's new position
		 */
		static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);

		/**
		 * Callback to capture mouse scroll events 
		 * @param window The window triggering the callback
		 * @param xOffset the horizontal value of the scroll action
		 * @param yOffset the vertical value of the scroll action
		 */
		static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		/**
		 * Get's the current rendering context's width
		 */
		int GetWindowWidth() const;

		/**
		 * Get's the current rendering context's height
		 */
		int GetWindowHeight() const;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		void ToggleCursor();

		/**
		 * Global function to allow any user to query data about the active window in a const fashion
		 */
		static const WindowManager* GetActiveWindow();

	private:
		/** 
		 * Performs initialization of the GLFW library
		 */
		void InitGLFW();

		/** 
		 * Performs initialization of the GLAD library 
		 */
		void InitGLAD();

		/**
		 * Toggle fullscreen
		 */
		void ToggleFullscreen();

		/** 
		 * Helper function to poll gamepad buttons 
		 * @param state The gamepad state to process
		 * @param timestamp The timestamp to affix to any reported input
		 */
		void PollGamepadButtons(GLFWgamepadstate& state, const utils::GameTime& timestamp);

		/** The game's window */
		std::shared_ptr<GLFWwindow> Window;

		/** The game's input manager */
		std::shared_ptr<InputManager> GameInputManager;
		
		/** The game's name */
		std::string GameName;

		/** The window's width */
		int WindowWidth;

		/** The window's height */
		int WindowHeight;

		/** Flag to determine if the current window is fullscreen */
		bool IsFullscreen;

		/** Flag to determine if the cursor is enabled in the window */
		bool CursorEnabled;

		/** Pointer to the active window manager to allow static callback functions to work properly */
		static WindowManager* CurrWindowManager;

		/** OpenGL Major version */
		static const int OPENGL_MAJOR = 4;

		/** OpenGL Minor version */
		static const int OPENGL_MINOR = 5;
	
		/** Static constant to earmark special Input for toggling fullscreen */
		static const KeyboardInput ToggleFullscreenInput;
	};

}