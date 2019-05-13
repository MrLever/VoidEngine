#pragma once
//STD Headers
#include <deque>

//Library Headers

//Coati Headers

namespace EngineCore {
	
	template <class T>
	class GenericInputInterface {
	private:

	protected:
		std::deque<T> EventQueue;
		int ID;
	
	public:
		GenericInputInterface(int id);
		~GenericInputInterface();
	
	public:
		std::deque<T> Poll();
		void ReportInput(T Input);
	};

	//tors
	template <class T>
	GenericInputInterface<T>::GenericInputInterface(int id) {
		ID = id;
	}

	template <class T>
	GenericInputInterface<T>::~GenericInputInterface() {

	}

	//Public Member Functions
	template<class T>
	std::deque<T> GenericInputInterface<T>::Poll() {
		auto Events = this->EventQueue;
		this->EventQueue = std::deque<T>();
		return Events;
	}

	template<class T>
	void GenericInputInterface<T>::ReportInput(T Input) {
		EventQueue.push_back(Input);
	}

}