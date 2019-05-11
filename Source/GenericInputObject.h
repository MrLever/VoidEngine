#pragma once
//STD Headers
#include <deque>

//Library Headers

//Coati Headers

namespace EngineCore {
	
	template <class T>
	class GenericInputObject {
	private:

	protected:
		std::deque<T> EventQueue;
		int ID;
	
	public:
		GenericInputObject(int id);
		~GenericInputObject();
	
	public:
		std::deque<T> Poll();
		void ReportInput(T Input);
	};

	//tors
	template <class T>
	GenericInputObject<T>::GenericInputObject(int id) {
		ID = id;
	}

	template <class T>
	GenericInputObject<T>::~GenericInputObject() {

	}

	//Public Member Functions
	template<class T>
	std::deque<T> GenericInputObject<T>::Poll() {
		auto Events = this->EventQueue;
		this->EventQueue = std::deque<T>();
		return Events;
	}

	template<class T>
	void GenericInputObject<T>::ReportInput(T Input) {
		EventQueue.push_back(Input);
	}

}