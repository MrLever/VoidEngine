#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Void Engine Headers
#include "core/Window.h"

//Forward class declaration
struct GLFWwindow;

namespace platform {
	class WindowsWindow : public core::Window {
	public:
		/**
		 * Constructor
		 * @param data The parameters to use in creating the window's context
		 */
		WindowsWindow(core::EventBus* bus, core::WindowData& data);

		/**
		 * Destructor
		 */
		~WindowsWindow();
		
		/**
		 * Instructs engine to process the window's message queue
		 */
		void ProcessEvents() override;

		/**
		 * Instructs window to poll and report gamepad input
		 */
		void PollGamepadInput() override;

		/**
		 * Instructs the window to swap buffers, drawing the result of the last render frame
		 */
		void SwapBuffers() override;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		void SetCursorCapture(bool state) override;

		/**
		 * Instructs GLFW to toggle cursor visibility
		 */
		void ToggleCursorCapture() override;

		/**
		 * Callback to display GLFW errors
		 * @param error The error's numerical code
		 * @param description The Error's description
		 */
		static void ReportWindowError(int error, const char* description);

	protected:
		/**
		 * Helper function that forces OS specific window systems to expose a rendering API
		 */
		void CreateRenderingContext() override;

		/**
		 * Toggle fullscreen
		 */
		void ToggleFullscreen() override;

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

		/** */
		GLFWwindow* GLFWContext;
		
		/** OpenGL Major version */
		static const int OPENGL_MAJOR = 4;

		/** OpenGL Minor version */
		static const int OPENGL_MINOR = 5;

	};
}