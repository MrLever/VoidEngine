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
		GenericInputInterface(int id);
		~GenericInputInterface();
	
	public:
		void PublishInput(const GenericInputPtr input);

		InputReport Poll();
	};
}