#pragma once
//STD Headers
#include <string>

//Library Headers


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

	private:
		//Private class members
		std::string Event;
		MessageType Type;
		unsigned long long ID;

	public:
		Message(const std::string &message, const MessageType &type);
		Message(const std::string &message, unsigned type);
		~Message();

		bool operator==(const Message& other) const;

	private:
		//Private member functions

	public:
		//Public member functions
		std::string GetEvent() const;
		unsigned long long GetEventID() const;
		MessageType GetType() const;

	};

}


//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::Message> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const EngineCore::Message& t) const {
			return t.GetEventID();
		}

	};
}