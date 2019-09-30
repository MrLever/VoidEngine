#pragma once

//STD Headers
#include <unordered_map>
#include <functional>

//Library Headers

//Coati Headers
#include "Message.h"

namespace core {
	/**
	 * @class EventTable 
	 * @brief Data structure to represent a map of Message -> Callable
	 */
	class EventTable {
	public:
		/**
		 * Constructor
		 */
		EventTable() = default;
		
		/**
		 * Destructor
		 */
		~EventTable() = default;

		/**
		 * Array index access overload
		 * @param event The event to lookup in the events map
		 */
		std::function<void()> operator[] (const Message& event) const;

		/**
		 * Adds an entry to the Event map
		 * @param message The Event Key
		 * @param event The Event Action
		 */
		bool BindEvent(const Message &message, const std::function<void()> &action);

		/**
		 * Removes an element from the event table
		 * @param message The message to unbind
		 */
		bool UnbindEvent(const Message &message);

	private:
		/** A map of Message -> Callable */
		std::unordered_map<Message, std::function<void()>> Events;
	};

}