//STD Headers
#include <iostream>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "Window.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "InputAxisReport.h"
#include "Logger.h"
#include "WindowClosedEvent.h"
#include "WindowResizedEvent.h"
#include "MouseButtonEvent.h"
#include "PauseGameEvent.h"
#include "MouseMovedEvent.h"
#include "KeyboardInputEvent.h"

namespace core {
	Window* Window::CurrWindowManager = nullptr;
	
	const KeyboardInput Window::ToggleFullscreenInput(
		KeyboardButton::ENTER, 
		ButtonState::PRESSED, 
		InputModifier::ALT
	);

	Window::Window(EventBus* bus, WindowData& data) : EventBusNode(bus) {
		
		WindowWidth = data.windowWidth;
		WindowHeight = data.windowHeight;
		GameName = data.gameName;

		InitGLFW();
		InitGLAD();

		CurrWindowManager = this;
	}


	Window::~Window() {
		glfwTerminate();
	}

	void Window::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<PauseGameEvent>(
			[this](PauseGameEvent* event) {
				ToggleCursorCapture();
			}
		);
	}

	unsigned Window::GetSubscription() {
		return 
			static_cast<unsigned>(EventCategory::WINDOW) |
			static_cast<unsigned>(EventCategory::GAMEPLAY);
	}

	int Window::GetWindowWidth() const {
		return WindowWidth;
	}

	int Window::GetWindowHeight() const {
		return WindowHeight;
	}

	void Window::SetView(Entity* parent, CameraComponent* comp) {
		utils::Logger::LogDebug("Entity " + parent->GetName() + " has set the window's viewport to its camera");

		ActiveCamera = comp;
	}

	CameraComponent* Window::GetView() {
		return ActiveCamera;
	}

	Window* Window::GetActiveWindow(){
		return CurrWindowManager;
	}

	void Window::InitGLFW() {
		if (glfwInit() == GLFW_FALSE) {
			// Initialization failed
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		GLFWContext = std::shared_ptr<GLFWwindow>(
			glfwCreateWindow(WindowWidth, WindowHeight, GameName.c_str(), nullptr, nullptr),
			DeleteWindow
		);

		if (GLFWContext == nullptr) {
			glfwSetWindowShouldClose(GLFWContext.get(), GLFW_TRUE);
		}

		glfwMakeContextCurrent(GLFWContext.get());
		glfwSetWindowUserPointer(GLFWContext.get(), this);
		
		//Setup callbacks
		glfwSetWindowCloseCallback(
			GLFWContext.get(), 
			[](GLFWwindow* context) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);
				window->PublishEvent(new WindowClosedEvent());
			}
		);

		glfwSetFramebufferSizeCallback(
			GLFWContext.get(), 
			[](GLFWwindow* context, int width, int height) {
				glViewport(0, 0, width, height);

				Window* window = (Window*)glfwGetWindowUserPointer(context);
				window->WindowWidth = width;
				window->WindowHeight = height;
				
				window->PublishEvent(new WindowResizedEvent(width, height));
			}
		);

		glfwSetKeyCallback(
			GLFWContext.get(),
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

				window->PublishEvent(new KeyboardInputEvent(input));
			}
		);

		glfwSetMouseButtonCallback(GLFWContext.get(), 
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

		glfwSetCursorPosCallback(GLFWContext.get(),
			[](GLFWwindow* context, double xPos, double yPos) {
				Window* window = (Window*)glfwGetWindowUserPointer(context);
				window->PublishEvent(new MouseMovedEvent(xPos, yPos));
			}
		);

		SetCursorCapture(true);
	}

	void Window::InitGLAD() {
		auto GLADaddress = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
		bool success = gladLoadGLLoader(GLADaddress) == 0;
		if (success) {
			utils::Logger::LogError("Failed to initialize GLAD");
			std::terminate();
		}

		glViewport(0, 0, WindowWidth, WindowHeight);
	}

	void Window::ToggleFullscreen() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		const int RESTORE_WIDTH = 640;
		const int RESTORE_HEIGHT = 480;
		if (!IsFullscreen) {
			WindowWidth = mode->width;
			WindowHeight = mode->height;

			glfwSetWindowMonitor(
				GLFWContext.get(), 
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
				GLFWContext.get(), 
				NULL, mode->width / 2, mode->height / 2, 
				RESTORE_WIDTH, RESTORE_HEIGHT, 
				GLFW_DONT_CARE
			);
			IsFullscreen = false;
		}

		glViewport(0, 0, WindowWidth, WindowHeight);
	}

	void Window::SetCursorCapture(bool state) {
		if (state) {
			glfwSetInputMode(GLFWContext.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			CursorEnabled = false;
		}
		else {
			glfwSetInputMode(GLFWContext.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			CursorEnabled = true;
		}
	}

	void Window::ToggleCursorCapture() {
		CursorEnabled = !CursorEnabled;
		if (CursorEnabled) {
			glfwSetInputMode(GLFWContext.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(GLFWContext.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	std::shared_ptr<GLFWwindow> Window::GetWindow() {
		return GLFWContext;
	}

	void Window::PollEvents() {
		glfwPollEvents();

		if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
			HandleGamepadInput();
		}

	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(GLFWContext.get());
	}

	void Window::SetInputManager(std::shared_ptr<InputManager> inputManager) {
		GameInputManager = std::move(inputManager);
	}

	void Window::HandleGamepadInput() {
		GLFWgamepadstate state;
		static const float JOYSTICK_DEADZONE = 0.2;
		auto timestamp = utils::GetGameTime();

		PollGamepadButtons(state, timestamp);
		
		//Process axes
		static InputAxisReport LeftJoyX("RightAxis", 0);
		static InputAxisReport LeftJoyY("UpAxis", 0);
		static InputAxisReport RightJoyX("LookRight", 0);
		static InputAxisReport RightJoyY("LookUp", 0);

		//The following axes lookups are inverted intentionally.
		LeftJoyX.Value = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
		LeftJoyY.Value = -state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
		RightJoyX.Value = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
		RightJoyY.Value = -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

		if ((LeftJoyX.Value > JOYSTICK_DEADZONE) || (LeftJoyX.Value < -JOYSTICK_DEADZONE)) {
			GameInputManager->ReportInput(LeftJoyX);
		}
		if ((LeftJoyY.Value > JOYSTICK_DEADZONE) || (LeftJoyY.Value < -JOYSTICK_DEADZONE)) {
			GameInputManager->ReportInput(LeftJoyY);
		}
		if ((RightJoyX.Value > JOYSTICK_DEADZONE) || (RightJoyX.Value < -JOYSTICK_DEADZONE)) {
			GameInputManager->ReportInput(RightJoyX);
		}
		if ((RightJoyY.Value > JOYSTICK_DEADZONE) || (RightJoyY.Value < -JOYSTICK_DEADZONE)) {
			GameInputManager->ReportInput(RightJoyY);
		}
	}

	void Window::PollGamepadButtons(GLFWgamepadstate& state, const utils::GameTime& timestamp){
		if (!glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
			return;
		}

		//Process Buttons
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]) {
			GameInputManager->ReportInput(
				GamepadInput(GamepadButton::DPAD_LEFT, ButtonState::PRESSED, timestamp)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]) {
			GameInputManager->ReportInput(
				GamepadInput(GamepadButton::DPAD_RIGHT, ButtonState::PRESSED, timestamp)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]) {
			GameInputManager->ReportInput(
				GamepadInput(GamepadButton::DPAD_UP, ButtonState::PRESSED, timestamp)
			);
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN]) {
			GameInputManager->ReportInput(
				GamepadInput(GamepadButton::DPAD_DOWN, ButtonState::PRESSED, timestamp)
			);
		}
	}

	void Window::DeleteWindow(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}

	void Window::ReportWindowError(int error, const char* description) {
		std::stringstream errorMsg;
		errorMsg << "Error: #" << error << ", " << description;

		utils::Logger::LogError(errorMsg.str());
	}

}