#pragma once
//STD Headers
#include <string>
#include <functional>
#include <iostream>

//Library Headers

//Coati Headers

namespace EngineCore {
	enum class ActionType : unsigned {
		Error = 0,
		Discrete = 1,
		Continuous = 2,
	};

	class Action {
	
	private:
		std::string ActionName;
		unsigned long long ActionID;

		ActionType Type;

		std::function<void()> Event;

	public:
		Action(std::string name, ActionType type);
		Action(std::string name, ActionType type, std::function<void()> event);
		~Action();

		bool operator==(const Action& other) const;

	private:

	public:
		std::string GetName() const;
		unsigned long long GetID() const;
		ActionType GetAction();

		void BindAction(std::function<void()> newAction);
		void TriggerAction();
		

	};

}