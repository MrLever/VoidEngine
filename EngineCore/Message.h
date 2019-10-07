#pragma once
//STD Headers
#include <string>
#include <iostream>

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	//Forward Declarations

	enum class MessageType : unsigned {
		Log = 1,
		Initialization = 2,
		Input = 4,
		GenericEvent = 8,
		Error = 16,
		Termination = 32,
		NACK = 0,
		ACK = 0xFFFFFFFF
	};


	class Message {
	public:
		/**
		 * Constructor
		 * @param message The body of the message
		 * @param type The message type flag
		 */
		Message(const std::string &message, const MessageType &type);

		/**
		 * Constructor
		 * @param message The body of the message
		 * @param type The message type flag
		 */
		Message(const std::string &message, unsigned type);

		/**
		 * Destructor
		 */
		~Message();

		/**
		 * Equality comparison operator
		 * @param other The other message to compare against
		 */
		bool operator==(const Message& other) const;

		friend std::ostream& operator << (std::ostream& out, const Message& message);

		/**
		 * Returns the message body of this event
		 */
		std::string GetEvent() const;

		/**
		 * Returns the UniqueID of this message for fast comparisons
		 */
		utils::Name GetEventID() const;

		/**
		 * Gets this message's type
		 */
		MessageType GetType() const;

	private:
		/** The body of the message */
		std::string Event;
		
		/** The type of the message */
		MessageType Type;

		/** Message ID based on a hash of the message body */
		utils::Name ID;
	};

}


//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> 
	struct hash<core::Message> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const core::Message& t) const {
			return t.GetEventID().ID;
		}
	};
}