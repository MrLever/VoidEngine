//STD Headers

//Library Headers

//Coati Headers
#include "GenericInputInterface.h"
#include "TimeUtils.h"

namespace EngineCore {
	//tors
	GenericInputInterface::GenericInputInterface(int id) : ID(id) {

	}

	GenericInputInterface::~GenericInputInterface() {
	
	}

	void GenericInputInterface::PublishInput(const GenericInputPtr input) {
		EventQueue.push_back(input);
		HistoryQueue.push_back(input);

		EngineCore::GameTime now = EngineCore::GetGameTime();

		//Clear old history data on report.
		while (now - HistoryQueue.front()->GetTimeStamp() > HistoryLifetime) {
			HistoryQueue.pop_front();
			if (HistoryQueue.empty()) [[unlikely]] {
				break;
			}
		}
	}

	InputReport GenericInputInterface::Poll() {
		auto report = InputReport(HistoryQueue, EventQueue);

		EventQueue = std::deque<GenericInputPtr>();

		return report;
	}

}

