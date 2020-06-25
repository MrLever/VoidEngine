#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers

//Void Engine Headers
#include "utils/EngineUtilities.h"

#include "core/event_system/EventSystem.h"
#include "core/input/definitions/KeyboardInput.h"
#include "core/rendering/Viewport.h"

namespace core {

	struct WindowData {
		std::string gameName;
		int windowWidth;
		int windowHeight;
	};

	/**
	 * @class Window
	 * @brief Object to manage the OS-specific window/input context.
	 */
	class Window : public EventListener {

	public:
		/**
		 * Constructor
		 * @param data The parameters to use in creating the window's context
		 */
		Window(EventSystem* eventSystem, WindowData& data);
		
		/**
		 * Destructor
		 */
		virtual ~Window();

		/**
		 * Instructs engine to process the window's message queue
		 */
		virtual void ProcessEvents() = 0;

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		virtual void SwapBuffers() = 0;
		
		/**
		 * Sets window size and generates a new WindowResizedEvent
		 */
		virtual void SetWindowSize(int width, int height);

		Viewport GetViewport() const;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		virtual void SetCursorCapture(bool state) = 0;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		virtual void ToggleCursorCapture() = 0;

	protected:
	
		/**
		 * Toggle fullscreen
		 */
		virtual void ToggleFullscreen() = 0;

		/**
		 * Instructs window to poll and report gamepad input
		 */
		virtual void PollGamepadInput() = 0;

		/** The game's name */
		std::string m_WindowText;

		/** Flag to determine if the current window is fullscreen */
		bool m_IsFullscreen;

		/** Flag to determine if the cursor is enabled in the window */
		bool m_CursorEnabled;

		Viewport m_Viewport;
	};
}

using WindowPtr = std::shared_ptr<core::Window>;