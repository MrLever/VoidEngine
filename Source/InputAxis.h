#pragma once
//STD Headers
#include <unordered_map>
#include <list>
#include <string>

//Library Headers

//Coati Headesr
#include "KeyboardInput.h"
#include "EngineUtilities.h"

namespace EngineCore {

	class InputAxis	{

	private:
		double AxisValue;
		std::unordered_map<KeyType, double> AxisBindings;
		std::list<KeyType> CommandQueue;
		std::string ID;


	public:
		InputAxis(std::string AxisName);
		~InputAxis();
	
		bool operator==(const InputAxis& other);
	private:
		void TriggerBinding(const EngineCore::KeyboardInput& input);
		void ReleaseBinding(const EngineCore::KeyboardInput& input);

	public:
		void AddBinding(KeyType input, double scale);
		std::string GetID() const;
		
		void UpdateAxis(const KeyboardInput &input);
		void Reset();
		
		double Poll() const;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::InputAxis> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const EngineCore::InputAxis& axis) const {
			return EngineUtilities::FNV1aHash(axis.GetID());
		}

	};
}