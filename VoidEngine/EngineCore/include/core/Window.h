#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Void Engine Headers
#include "utils/EngineUtilities.h"

#include "core/event_system/EventBusNode.h"
#include "core/input/definitions/KeyboardInput.h"
#include "core/rendering/RenderingContext.h"

namespace core {
	//Forward Class Declarations
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
		 * @param data The parameters to use in creating the window's context
		 */
		Window(EventBus* bus, WindowData& data);
		
		/**
		 * Destructor
		 */
		virtual ~Window();

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
		 * Instructs engine to process the window's message queue
		 */
		virtual void ProcessEvents();

		/**
		 * Instructs window to poll and report gamepad input
		 */
		virtual void PollGamepadInput();

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		virtual void SwapBuffers();
		
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
		virtual void SetCursorCapture(bool state);

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		virtual void ToggleCursorCapture();

		RenderingContext* GetRenderingContext();

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

	protected:
		/**
		 * Toggle fullscreen
		 */
		virtual void ToggleFullscreen();

		/** Interface to the type of rendering context bound to the window during creation */
		RenderingContext* RenderingAPI;

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
		 * Helper function to poll gamepad buttons 
		 * @param state The gamepad state to process
		 * @param timestamp The timestamp to affix to any reported input
		 */
		void PollGamepadButtons(GLFWgamepadstate& state, const utils::GameTime& timestamp);

		/**
		 * Helper function to poll gamepad axes
		 * @param state The gamepad state to process
		 */
		void PollGamepadAxes(GLFWgamepadstate& state);

		/** The game's window */
		std::shared_ptr<GLFWwindow> GLFWContext;

		/** The active camera to be used for rendering */
		CameraComponent* ActiveCamera;
		
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

using WindowPtr = std::shared_ptr<core::Window>;