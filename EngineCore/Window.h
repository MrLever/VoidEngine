#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Void Engine Headers
#include "EngineUtilities.h"
#include "KeyboardInput.h"
#include "EventBusNode.h"

namespace core {
	//Forward Class Declarations
	class InputManager;
	class CameraComponent;
	class Entity;

	struct WindowData {
		std::string gameName;
		int windowWidth;
		int windowHeight;
	};

	/**
	 * @class Window
	 * @brief Object to manage the OS-specific window/input context.
	 */
	class Window : public EventBusNode {

	public:
		/**
		 * Constructor
		 * @param gameName The name to display in the game's window title bar
		 * @param windowWidth The width of the game window
		 * @param windowHeight The height of the game window
		 */
		Window(EventBus* bus, WindowData& data);
		
		/**
		 * Destructor
		 */
		~Window();

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		void ReceiveEvent(Event* event) override;

		/**
		 * Allows EventBus to query the node's subscription, and filter events accordingly
		 */
		virtual unsigned GetSubscription() override;

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
		void SetCursorCapture(bool state);

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		void ToggleCursorCapture();

		/**
		 * Global function to allow an entity to set the window's view of the world
		 * @param parent The entity requesting this set. Used for victim blaming
		 * @param comp The camera that is being set as active
		 */
		void SetView(Entity* parent, CameraComponent* comp);

		/**
		 * Global function to allow an the renderer get the window's view of the world
		 */
		CameraComponent* GetView();

		/**
		 * Global function to allow any user to query data about the active window
		 */
		static Window* GetActiveWindow();

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
		std::shared_ptr<GLFWwindow> GLFWContext;

		/** The game's input manager */
		std::shared_ptr<InputManager> GameInputManager;

		/** The active camera to be used for rendering */
		CameraComponent* ActiveCamera;
		
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
		static Window* CurrWindowManager;

		/** OpenGL Major version */
		static const int OPENGL_MAJOR = 4;

		/** OpenGL Minor version */
		static const int OPENGL_MINOR = 5;
	
		/** Static constant to earmark special Input for toggling fullscreen */
		static const KeyboardInput ToggleFullscreenInput;
	};
}

using WindowManagerPtr = std::shared_ptr<core::Window>;