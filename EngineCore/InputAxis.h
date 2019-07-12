#pragma once
//STD Headers
#include <unordered_map>
#include <list>
#include <string>

//Library Headers

//Coati Headesr
#include "KeyboardInput.h"
#include "UUID.h"

namespace EngineCore {

	class InputAxis	{

	private:
		std::unordered_map<KeyboardButton, double> AxisBindings;
		std::list<KeyboardButton> CommandQueue;
		
		double AxisValue;
		std::string AxisName;
		EngineUtils::UUID AxisID;


	public:
		InputAxis(std::string AxisName);
		~InputAxis();
	
		bool operator==(const InputAxis& other);
	private:
		void TriggerBinding(const KeyboardInputPtr input);
		void ReleaseBinding(const KeyboardInputPtr input);

	public:
		void AddBinding(KeyboardButton input, double scale);
		EngineUtils::UUID GetID() const;
		
		void UpdateAxis(const KeyboardInputPtr input);
		void Reset();
		
		double Poll() const;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> 
	struct hash<EngineCore::InputAxis> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const EngineCore::InputAxis& axis) const {
			return axis.GetID().ID;
		}

	};
}