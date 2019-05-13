#pragma once
//STD Headers

//Library Headers

namespace EngineCore {

	//Forward Class declarations

	enum class KeyType : unsigned {
		ESC = 256,
		W = 87,
		A = 65,
		S = 83,
		D = 68,
		NUM_9 = 329
	};

	enum class ButtonState : unsigned {
		Released = 0,
		Pressed = 1,
		Held = 2,
		Any = 4
	};

	class KeyboardInput {
	
	private:
		//Private Class Members
		KeyType Key;
		ButtonState State;
		double TimeStamp;

	public:
		//CTORS
		KeyboardInput(KeyType key, ButtonState state);
		KeyboardInput(KeyType key, ButtonState state, double time);
		~KeyboardInput();

		bool operator==(const KeyboardInput& other) const;

	private:

	public:
		KeyType GetKey() const;
		ButtonState GetKeyState() const;

		std::size_t Hash() const;

	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::KeyboardInput> { //Class to define hash function for Keyboard Input
		
		//Hash functor
		std::size_t operator()(const EngineCore::KeyboardInput& t) const {
			return t.Hash();
		}
	
	};
}