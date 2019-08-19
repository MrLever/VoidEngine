#pragma once
//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "UUID.h"

namespace EngineCore {

	//Forward Declarations

	enum class MessageType : unsigned {
		Initialization = 1,
		Input = 2,
		GenericEvent = 4,
		Error = 8,
		Termination = 16,
		DebugNACK = 0,
		DebugACK = 0xFFFFFFFF
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

		/**
		 * Returns the message body of this event
		 */
		std::string GetEvent() const;

		/**
		 * Returns the UniqueID of this message for fast comparisons
		 */
		EngineUtils::UUID GetEventID() const;

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
		EngineUtils::UUID ID;
	};

}


//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> 
	struct hash<EngineCore::Message> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const EngineCore::Message& t) const {
			return t.GetEventID().ID;
		}
	};
}