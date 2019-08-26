#pragma once
//STD Headers
#include <deque>
#include <vector>
#include <memory>

//Library Headers

//Coati Headers
#include "Input.h"
#include "EngineUtilities.h"

namespace EngineCore {
	/**
	 * @struct InputReport
	 * @brief Container for returning input data to input manager
	 * @tparam U The type of input contained in the report
	 */
	template <class U>
	struct [[nodiscard]] InputReport{
		std::vector<U> History;
		std::vector<U> Inputs;

		InputReport(std::deque<U> history, std::deque<U> newInputs) {
			History = std::vector<U>(history.begin(), history.end());
			Inputs = std::vector<U>(newInputs.begin(), newInputs.end());
		}
	};

	/**
	 * @class InputInterface
	 * @brief Presents a interface for interacting with a HID
	 * @tparam T The type of input events this interface handles
	 */
	template <class T>
	class InputInterface {
	public:
		/**
		 * Constructor
		 */
		InputInterface() = default;

		/**
		 * Destructor
		 */
		~InputInterface() = default;

		/**
		 * Records an incomming input event from an HID for future polling
		 * @param input The input to record
		 */
		void PublishInput(const T& input);

		/**
		 * Reports input events since the last poll
		 * @return An input report that can be parsed for higher-order input events
		 */
		InputReport<T> Poll();
	
	protected:
		/** Time in ms input events should be kept in the input history for */
		static const int HISTORY_LIFETIME = 500;

		/** A double-ended queue of old input events */
		std::deque<T> HistoryQueue;

		/** A double-ended queue of old input events */
		std::deque<T> EventQueue;
	};

	template<class T>
	void InputInterface<T>::PublishInput(const T& input) {
		EventQueue.push_back(input);
		
		EngineUtils::GameTime now = EngineUtils::GetGameTime();

		if (!HistoryQueue.empty()) {
			//Clear old history data on report.
			while (now - HistoryQueue.front().GetTimeStamp() > HISTORY_LIFETIME) {
				HistoryQueue.pop_front();
				if (HistoryQueue.empty()) [[unlikely]] {
					break;
				}
			}
		}
	}

	template<class T>
	InputReport<T> InputInterface<T>::Poll() {
		auto report = InputReport(HistoryQueue, EventQueue);
		
		//Transfer last frame's input into history
		for (auto input : EventQueue) {
			HistoryQueue.push_back(input);
		}
		
		//Clear event queue
		EventQueue = std::deque<T>();

		return report;
	}
}