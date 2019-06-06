#pragma once
//STD Headers
#include <deque>
#include <vector>
#include <memory>

//Library Headers

//Coati Headers
#include "GenericInput.h"
#include "EngineUtilities.h"

namespace EngineCore {
	struct [[nodiscard]] InputReport {
		std::vector<GenericInputPtr> History;
		std::vector<GenericInputPtr> Inputs;

		InputReport(std::deque<GenericInputPtr> history, std::deque<GenericInputPtr> newInputs) {
			History = std::vector<GenericInputPtr>(history.begin(), history.end());
			Inputs = std::vector<GenericInputPtr>(newInputs.begin(), newInputs.end());
		}
	};

	class GenericInputInterface {
	private:


	protected:
		static const int HistoryLifetime = 500;
		std::deque<GenericInputPtr> HistoryQueue;
		std::deque<GenericInputPtr> EventQueue;

		int ID;
	
	public:
		GenericInputInterface(int id) : ID(id) {

		}
		~GenericInputInterface() = default;
	
	public:
		void PublishInput(const GenericInputPtr input) {
			EventQueue.push_back(input);
			HistoryQueue.push_back(input);

			EngineUtilities::GameTime now = EngineUtilities::GetGameTime();

			//Clear old history data on report.
			while (now - HistoryQueue.front()->GetTimeStamp() > HistoryLifetime) {
				HistoryQueue.pop_front();
				if (HistoryQueue.empty()) [[unlikely]] {
					break;
				}
			}

		}

		InputReport Poll() {
			auto report = InputReport(HistoryQueue, EventQueue);

			EventQueue = std::deque<GenericInputPtr>();

			return report;
		}
	};
}