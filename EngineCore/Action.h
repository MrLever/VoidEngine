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
	
	public:
		/**
		 * Constructor
		 * @param name The name of the action
		 * @param type The action's type
		 */
		Action(const std::string& name, ActionType type);

		/**
		 * Constructor
		 * @param name The name of the action
		 * @param type The action's type
		 * @param event The callable behavior associated with this action
		 */
		Action(const std::string& name, ActionType type, const std::function<void()>& event);

		/**
		 * Destructor
		 */
		~Action();

		/**
		 * Equality comparision overload
		 * @param other The action to compare to this one
		 */
		bool operator== (const Action& other) const;

		/**
		 * Functor operator overload
		 */
		void operator() () const;

		/**
		 * Get's this objects UUID
		 * @return the Object's ID
		 */
		EngineUtils::UUID GetID() const;

		/**
		 * Get the Action's type
		 * @return the Action's type
		 */
		ActionType GetActionType();

		/** 
		 * Bind a behavior to this action
		 */
		void BindAction(std::function<void()> newAction);

	private:
		/** Hash of the objects name for fast comparisions */
		EngineUtils::UUID ActionID;

		/** This action's type */
		ActionType Type;

		/** The event this action binds to */
		std::function<void()> Event;
	};

}