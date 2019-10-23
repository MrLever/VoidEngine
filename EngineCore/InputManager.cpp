//STD Headers
#include <memory>
#include <utility>

//Library Headers

//Void Engine Headers
#include "InputManager.h"
#include "EventBus.h"
#include "MouseButtonEvent.h"
#include "MouseMovedEvent.h"
#include "PauseGameEvent.h"
#include "Level.h"

namespace core {

	InputManager::InputManager(
		EventBus* bus, 
		const utils::ResourceHandle<utils::Configuration>& configuration
		) : EventBusNode(bus), Configurable(configuration) {
		
		Configure();
	}

	void InputManager::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<KeyboardInputEvent>(
			[this](KeyboardInputEvent* event) {
				ReportInput(event->Input);
			}
		);

		dispatcher.Dispatch<MouseButtonEvent>(
			[this](MouseButtonEvent* event) {
				ReportInput(event->Input);
			}
		);

		dispatcher.Dispatch<MouseMovedEvent>(
			[this](MouseMovedEvent* event) {
				static double MouseXPrev = -1.0f;
				static double MouseYPrev = -1.0f;
				static float SENSITIVITY = 0.05f;
				static InputAxisReport MouseX("LookRight", 0);
				static InputAxisReport MouseY("LookUp", 0);

				if (MouseXPrev == -1.0f || MouseYPrev == 1.0f) {
					MouseXPrev = float(event->Position.X);
					MouseYPrev = float(event->Position.Y);
				}

				MouseX.Value = (float)(event->Position.X - MouseXPrev) * SENSITIVITY;
				MouseY.Value = (float)(MouseYPrev - event->Position.Y) * SENSITIVITY;

				MouseXPrev = event->Position.X;
				MouseYPrev = event->Position.Y;
				ReportInput(MouseX);
				ReportInput(MouseY);
			}
		);
	}

	unsigned InputManager::GetSubscription() {
		return static_cast<unsigned>(EventCategory::RAW_INPUT);
	}

	void InputManager::ReportInput(const KeyboardInput& input) {
		static const KeyboardInput PAUSE_INPUT(KeyboardButton::ESC, ButtonState::PRESSED);
		if (input == PAUSE_INPUT) {
			Bus->PostEvent(new PauseGameEvent());
		}

		auto button = input.GetButton();
		if (KeyboardAxisBindings.find(button) != KeyboardAxisBindings.end()) {
			KeyboardAxisBindings[button]->UpdateAxis(input);
			return;
		}

		KeyboardInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const MouseInput& input) {
		MouseInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const GamepadInput& input) {
		GamepadInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const InputAxisReport& input){
		InputAxisDataBuffer.push_back(input);
	}

	void InputManager::ProcessInput(Level* scene, float deltaTime) {
		//Process Mouse Input

		auto entities = scene->GetScene();

		while (!MouseInputBuffer.empty()) {
			auto button = MouseInputBuffer.front();

			std::string eventType;

			if (button.GetButton() == MouseButton::LEFT) {
				eventType = "Fire";
			}

			DispatchEvent(entities, InputEvent(eventType), deltaTime);

			MouseInputBuffer.pop_front();
		}

		//Process KB like mouse
		while (!KeyboardInputBuffer.empty()) {
			auto input = KeyboardInputBuffer.front();
			auto button = input.GetButton();
			KeyboardInputBuffer.pop_front();

			std::string eventType;

			if (KeyboardAxisBindings.find(button) != KeyboardAxisBindings.end()) {
				continue;
			}

			DispatchEvent(entities, InputEvent(eventType), deltaTime);
		}

		//Dispatch Axes updates
		for (auto& entry : KeyboardAxisBindings) {
			DispatchEvent(
				entities,
				entry.second->Poll(),
				deltaTime
			);
		}

		//Process Gamepad input
		while (!GamepadInputBuffer.empty()) {
			auto input = GamepadInputBuffer.front();
			auto button = input.GetButton();
			std::string eventType;

			if (button == GamepadButton::DPAD_UP) {
				InputAxisDataBuffer.push_back(
					InputAxisReport("UpAxis", 1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_DOWN) {
				InputAxisDataBuffer.push_back(
					InputAxisReport("UpAxis", -1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_LEFT) {
				InputAxisDataBuffer.push_back(
					InputAxisReport("RightAxis", -1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_RIGHT) {
				InputAxisDataBuffer.push_back(
					InputAxisReport("RightAxis", 1.0f)
				);
			}

			DispatchEvent(entities, InputEvent(eventType), deltaTime);

			GamepadInputBuffer.pop_front();
		}

		while (!InputAxisDataBuffer.empty()) {
			auto axisReading = InputAxisDataBuffer.front();

			DispatchEvent(entities, axisReading, deltaTime);

			InputAxisDataBuffer.pop_front();
		}
	}

	void InputManager::Configure() {
		//Set up the axes and their bindings
		auto LeftRightAxis = std::make_shared<InputAxis>("RightAxis");
		LeftRightAxis->AddBinding(
			KeyboardInput(KeyboardButton::A, ButtonState::PRESSED), -1.0f
		);

		LeftRightAxis->AddBinding(
			KeyboardInput(KeyboardButton::D, ButtonState::PRESSED), 1.0f
		);

		auto UpDownAxis = std::make_shared<InputAxis>("UpAxis");
		UpDownAxis->AddBinding(
			KeyboardInput(KeyboardButton::W, ButtonState::PRESSED), 1.0f
		);
		UpDownAxis->AddBinding(
			KeyboardInput(KeyboardButton::S, ButtonState::PRESSED), -1.0f
		);


		//Set up bindings to route keys to the axes
		KeyboardAxisBindings.insert({
			KeyboardButton::A,
			LeftRightAxis
		});

		KeyboardAxisBindings.insert({
			KeyboardButton::D,
			LeftRightAxis
		});

		KeyboardAxisBindings.insert({
			KeyboardButton::W,
			UpDownAxis
		});

		KeyboardAxisBindings.insert({
			KeyboardButton::S,
			UpDownAxis
		});

	}

	void InputManager::DispatchEvent(
			const std::vector<core::Entity*>& scene, 
			const InputEvent& event,
			float deltaTime
		) {
		static const utils::Name ERROR_EVENT_ID("Error");

		if (event.EventName == ERROR_EVENT_ID) {
			return;
		}

		for (auto& entity : scene) {
			entity->Input(event, deltaTime);
		}
	}

	void InputManager::DispatchEvent(
		const std::vector<core::Entity*>& scene,
		const InputAxisReport& axisData,
		float deltaTime
	) {
		static const utils::Name ERROR_EVENT_ID("Error");

		for (auto& entity : scene) {
			entity->Input(axisData, deltaTime);
		}
	}

}