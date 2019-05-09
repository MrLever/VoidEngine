#pragma once
//STD Headers
#include <queue>

//Library Headers

//Coati Headers

namespace EngineCore {
	
	template <class T>
	class GenericInputObject {
	private:

	protected:
		std::queue<T> EventQueue;
		int ID;
	
	public:
		GenericInputObject(int id);
		~GenericInputObject();
	

		std::queue<T> Poll();
	};

	template <class T>
	GenericInputObject<T>::GenericInputObject(int id) {
		ID = id;
	}

	template <class T>
	GenericInputObject<T>::~GenericInputObject() {

	}

	template<class T>
	std::queue<T> GenericInputObject<T>::Poll() {
		auto Events = this->EventQueue;
		this->EventQueue = std::queue<T>();
		return Events;
	}

}