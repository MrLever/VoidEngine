#pragma once
//STD Headers
#include <string>
#include <functional>
#include <iostream>

//Library Headers

//SuperVoid Headers
#include "UUID.h"

namespace EngineCore {
	enum class ActionType : unsigned {
		Error = 0,
		Discrete = 1,
		Continuous = 2,
	};

	class Action {
	
	private:
		EngineUtils::UUID ActionID;

		ActionType Type;

		std::function<void()> Event;

	public:
		Action(std::string name, ActionType type);
		Action(std::string name, ActionType type, std::function<void()> event);
		~Action();

		//Operator overloads
		bool operator== (const Action& other) const;
		void operator() () const;


	private:

	public:
		EngineUtils::UUID GetID() const;
		ActionType GetActionType();

		void BindAction(std::function<void()> newAction);
	};

}