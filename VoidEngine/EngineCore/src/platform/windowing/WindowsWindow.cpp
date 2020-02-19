//STD Headers


//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Void Engine Headers
#include "utils/Logger.h"

#include "platform/windowing/WindowsWindow.h"
#include "platform/rendering/OpenGLRenderingContext.h"

#include "event_system/events/AxisInputEvent.h"
#include "event_system/events/WindowClosedEvent.h"
#include "event_system/events/WindowResizedEvent.h"
#include "event_system/events/MouseButtonEvent.h"
#include "event_system/events/PauseGameEvent.h"
#include "event_system/events/MouseMovedEvent.h"
#include "event_system/events/KeyboardButtonEvent.h"
#include "event_system/events/GamepadButtonEvent.h"

#include "input/definitions/AxisInput.h"
#include "input/definitions/GamepadInput.h"

using namespace core;

namespace platform {
	WindowsWindow::WindowsWindow(core::EventBus* bus, core::WindowData& data) 
		: Window(bus, data), GLFWContext(nullptr) {
		
		InitGLFW();
		InitGLAD();
		CreateRenderingContext();
	}

	WindowsWindow::~WindowsWindow() {
		glfwDestroyWindow(GLFWContext);
	}

	void WindowsWindow::ProcessEvents() {
		glfwPollEvents();

		if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
			PollGamepadInput();
		}

	}

	void WindowsWindow::PollGamepadInput() {
		GLFWgamepadstate state;
		auto timestamp = utils::GetGameTime();

		PollGamepadButtons(state, timestamp);

		PollGamepadAxes(state);
	}

	void WindowsWindow::SwapBuffers() {
		glfwSwapBuffers(GLFWContext);
	}

	void WindowsWindow::SetCursorCapture(bool state) {
		if (state) {
			glfwSetInputMode(GLFWContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			CursorEnabled = false;
		}
		else {
			glfwSetInputMode(GLFWContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			CursorEnabled = true;
		}
	}

	void WindowsWindow::ToggleCursorCapture() {
		CursorEnabled = !CursorEnabled;
		if (CursorEnabled) {
			glfwSetInputMode(GLFWContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(GLFWContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	void WindowsWindow::ReportWindowError(int error, const char* description) {
		std::stringstream errorMsg;
		errorMsg << "Error: #" << error << ", " << description;

		utils::Logger::LogError(errorMsg.str());
	}

	void WindowsWindow::CreateRenderingContext() {
		DeviceContext = std::make_shared<OpenGLRenderingContext>();
		DeviceContext->SetViewport(0, 0, WindowWidth, WindowHeight);
	}

	void WindowsWindow::ToggleFullscreen() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		const int RESTORE_WIDTH = 640;
		const int RESTORE_HEIGHT = 480;
		if (!IsFullscreen) {
			WindowWidth = mode->width;
			WindowHeight = mode->height;

			glfwSetWindowMonitor(
				GLFWContext,
				glfwGetPrimaryMonitor(),
				0, 0, WindowWidth, WindowHeight,
				GLFW_DONT_CARE
			);

			IsFullscreen = true;
		}
		else {
			WindowWidth = mode->width / 2;
			WindowHeight = mode->height / 2;
			glfwSetWindowMonitor(
				GLFWContext,
				NULL, mode->width / 2, mode->height / 2,
				RESTORE_WIDTH, RESTORE_HEIGHT,
				GLFW_DONT_CARE
			);
			IsFullscreen = false;
		}

		DeviceContext->SetViewport(0, 0, WindowWidth, WindowHeight);
	}

	void WindowsWindow::InitGLFW() {
		if (glfwInit() == GLFW_FALSE) {
			// Initialization failed
			utils::Logger::LogError("GLFW window failed to initialize");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		GLFWContext = glfwCreateWindow(WindowWidth, WindowHeight, GameName.c_str(), nullptr, nullptr);

		if (GLFWContext == nullptr) {
			glfwSetWindowShouldClose(GLFWContext, GLFW_TRUE);
		}

		glfwMakeContextCurrent(GLFWContext);
		glfwSetWindowUserPointer(GLFWContext, this);

		//Setup callbacks
		glfwSetWindowCloseCallback(
			GLFWContext,
			[](GLFWwindow* context) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);
				window->PublishEvent(new WindowClosedEvent());
			}
		);

		glfwSetFramebufferSizeCallback(
			GLFWContext,
			[](GLFWwindow* context, int width, int height) {
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(context);
				window->SetWindowSize(width, height);
			}
		);

		glfwSetKeyCallback(
			GLFWContext,
			[](GLFWwindow* context, int key, int scancode, int action, int mods) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);

				//IGNORE KEY HELD EVENTS
				if (static_cast<ButtonState>(action) == ButtonState::HELD) {
					return;
				}

				//Create Input wrapper object
				KeyboardInput input(
					static_cast<KeyboardButton>(key),
					static_cast<ButtonState>(action),
					mods,
					utils::GetGameTime()
				);

				window->PublishEvent(new KeyboardButtonEvent(input));
			}
		);

		glfwSetMouseButtonCallback(
			GLFWContext,
			[](GLFWwindow* context, int button, int action, int mods) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);

				//Create Void Engine MouseInput
				MouseInput input(
					static_cast<MouseButton>(button),
					static_cast<ButtonState>(action),
					mods,
					utils::GetGameTime()
				);

				window->PublishEvent(new MouseButtonEvent(input));
			}
		);

		glfwSetCursorPosCallback(
			GLFWContext,
			[](GLFWwindow* context, double xPos, double yPos) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);
				window->PublishEvent(new MouseMovedEvent(xPos, yPos));
			}
		);

		SetCursorCapture(true);

	}

	void WindowsWindow::InitGLAD() {
		auto GLADaddress = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
		bool success = gladLoadGLLoader(GLADaddress) == 0;
		if (success) {
			utils::Logger::LogError("Failed to initialize GLAD");
			std::terminate();
		}
	}

	void WindowsWindow::PollGamepadButtons(GLFWgamepadstate& state, const utils::GameTime& timestamp) {
		if (!glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
			return;
		}

		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]) {
			PublishEvent(
				new GamepadButtonEvent(
					GamepadInput(GamepadButton::DPAD_LEFT, ButtonState::PRESSED, timestamp)
				)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]) {
			PublishEvent(
				new GamepadButtonEvent(
					GamepadInput(GamepadButton::DPAD_RIGHT, ButtonState::PRESSED, timestamp)
				)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]) {
			PublishEvent(
				new GamepadButtonEvent(
					GamepadInput(GamepadButton::DPAD_UP, ButtonState::PRESSED, timestamp)
				)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN]) {
			PublishEvent(
				new GamepadButtonEvent(
					GamepadInput(GamepadButton::DPAD_DOWN, ButtonState::PRESSED, timestamp)
				)
			);
		}
	}

	void WindowsWindow::PollGamepadAxes(GLFWgamepadstate& state) {
		AxisInput LeftJoyX(RawAxisType::GAMEPAD_JOYSTICK_LEFT_X, state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
		AxisInput LeftJoyY(RawAxisType::GAMEPAD_JOYSTICK_LEFT_Y, -state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
		AxisInput RightJoyX(RawAxisType::GAMEPAD_JOYSTICK_RIGHT_X, state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
		AxisInput RightJoyY(RawAxisType::GAMEPAD_JOYSTICK_RIGHT_Y, -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);

		PublishEvent(new AxisInputEvent(LeftJoyX));
		PublishEvent(new AxisInputEvent(LeftJoyY));
		PublishEvent(new AxisInputEvent(RightJoyX));
		PublishEvent(new AxisInputEvent(RightJoyY));
	}


}