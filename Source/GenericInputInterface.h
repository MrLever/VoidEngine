#pragma once
//STD Headers
#include <deque>
#include <vector>

//Library Headers

//Coati Headers
#include "GenericInput.h"
#include "EngineUtilities.h"

namespace EngineCore {
	template <class V>
	struct [[nodiscard]] InputReport {
		std::vector<V> History;
		std::vector<V> Inputs;

		InputReport(std::deque<V> history, std::deque<V> newInputs) {
			History = std::vector<V>(history.begin(), history.end());
			Inputs = std::vector<V>(newInputs.begin(), newInputs.end());
		}
	};

	template <class T, typename U>
	class GenericInputInterface {
	private:


	protected:
		static const int HistoryLifetime = 500;
		std::deque<GenericInput<U>> HistoryQueue;
		std::deque<GenericInput<U>> EventQueue;

		int ID;
	
	public:
		GenericInputInterface(int id) : ID(id) {

		}
		~GenericInputInterface() = default;
	
	public:
		void PublishInput(const T& input) {
			EventQueue.push_back(input);
			HistoryQueue.push_back(input);

			EngineUtilities::GameTime now = EngineUtilities::GetGameTime();

			//Clear old history data on report.
			while (now - HistoryQueue.front().GetTimeStamp() > HistoryLifetime) {
				HistoryQueue.pop_front();
				if (HistoryQueue.empty()) [[unlikely]] {
					break;
				}
			}

		}

		InputReport<GenericInput<U>> Poll() {
			auto report = InputReport<GenericInput<U>>(HistoryQueue, EventQueue);

			EventQueue = std::deque<GenericInput<U>>();

			return report;
		}
	};
}