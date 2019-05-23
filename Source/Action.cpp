//STD Headers

//Library Headers

//Coati headers
#include "Action.h"
#include "EngineUtilities.h"

namespace EngineCore {

	//tors
	Action::Action(std::string name, ActionType type) : ActionName(name), Type(type) {
		ActionID = EngineUtilities::FNV1aHash(name);
		Event = nullptr;
	}

	Action::Action(std::string name, ActionType type, std::function<void()> event) : ActionName(name), Type(type), Event(event){
		ActionID = EngineUtilities::FNV1aHash(name);
	}


	Action::~Action() {

	}

	bool Action::operator==(const Action& other) const {
		return this->ActionID == other.ActionID;
	}

	//Public Member Functions
	std::string Action::GetName() const {
		return ActionName;
	}

	unsigned long long Action::GetID() const {
		return ActionID;
	}

	ActionType Action::GetAction() {
		return Type;
	}

	void Action::BindAction(std::function<void()> newAction) {
		this->Event = newAction;
	}

	void Action::TriggerAction() {
		if (Event == nullptr) {
			std::cerr << "Error, no action bound";
			return;
		}

		Event();
	}



}