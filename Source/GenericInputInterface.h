#pragma once
//STD Headers
#include <deque>
#include <vector>

//Library Headers

//Coati Headers
#include "GenericInput.h"

namespace EngineCore {
	template <class V>
	struct InputReport {
		std::vector<V> History;
		std::vector<V> Inputs;

		InputReport(std::deque<V> history, std::deque<V> newInputs){
		
		}
	};

	template <class T, typename U>
	class GenericInputInterface {
	private:

	protected:
		std::deque<GenericInput<U>> HistoryQueue;
		std::deque<GenericInput<U>> EventQueue;

		int ID;
	
	public:
		GenericInputInterface(int id);
		~GenericInputInterface() = default;
	
	public:
		void PublishInput(const T &Input);

		InputReport<GenericInput<U>> Poll();


	};


	template<class T, typename U>
	inline GenericInputInterface<T, U>::GenericInputInterface(int id) : ID(id){

	}

	template<class T, typename U>
	inline void GenericInputInterface<T, U>::PublishInput(const T &Input) {
		EventQueue.push_back(Input);
	}

	template<class T, typename U>
	inline InputReport<GenericInput<U>> GenericInputInterface<T, U>::Poll()	{
		auto report = InputReport<GenericInput<U>>(HistoryQueue, EventQueue);

		return report;
	}



}