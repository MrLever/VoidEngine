#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers

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
		unsigned GetSubscription() override;

		/**
		 * Instructs engine to process the window's message queue
		 */
		virtual void ProcessEvents() = 0;

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		virtual void SwapBuffers() = 0;
		
		virtual void SetWindowSize(int width, int height);

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
		virtual void SetCursorCapture(bool state) = 0;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		virtual void ToggleCursorCapture() = 0;

		/**
		 * Allows other systems to request the current Rendering API
		 */
		std::shared_ptr<RenderingContext> GetRenderingContext();

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
		 * Helper function that forces OS specific window systems to expose a rendering API
		 */
		virtual void CreateRenderingContext() = 0;
		
		/**
		 * Toggle fullscreen
		 */
		virtual void ToggleFullscreen() = 0;

		/**
		 * Instructs window to poll and report gamepad input
		 */
		virtual void PollGamepadInput() = 0;

		/** Interface to the type of rendering context bound to the window during creation */
		std::shared_ptr<RenderingContext> RenderingAPI;

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
		/** The active camera to be used for rendering */
		CameraComponent* ActiveCamera;
		
		/** Pointer to the active window manager to allow static callback functions to work properly */
		static Window* CurrWindowManager;
	
		/** Static constant to earmark special Input for toggling fullscreen */
		static const KeyboardInput ToggleFullscreenInput;
	};
}

using WindowPtr = std::shared_ptr<core::Window>;