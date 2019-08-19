//STD Headers

//Library Headers

//SuperVoid headers
#include "Action.h"


namespace EngineCore {

	//tors
	Action::Action(const std::string& name, ActionType type) : ActionID(name), Type(type) {
		Event = nullptr;
	}

	Action::Action(const std::string& name, ActionType type, const std::function<void()>& event) 
		: ActionID(name), Type(type), Event(event) {

	}


	Action::~Action() {

	}

	bool Action::operator== (const Action& other) const {
		return this->ActionID == other.ActionID;
	}

	void Action::operator() () const {
		if (Event) {
			Event();
		}
	}

	//Public Member Functions
	EngineUtils::UUID Action::GetID() const {
		return ActionID;
	}

	ActionType Action::GetActionType() {
		return Type;
	}

	void Action::BindAction(std::function<void()> newAction) {
		this->Event = newAction;
	}
}