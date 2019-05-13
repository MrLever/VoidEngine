#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "GenericInput.h"

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

	class KeyboardInput : public GenericInput<KeyType> {
	
	private:

	public:
		//CTORS
		KeyboardInput(KeyType key, ButtonState state);
		KeyboardInput(KeyType key, ButtonState state, double time);
		~KeyboardInput();

		bool operator==(const KeyboardInput& other) const;

	private:

	public:
		std::size_t Hash() const override;

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