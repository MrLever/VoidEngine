#pragma once
//STD Headers
#include <unordered_map>

//Library Headers

//Void Engine Headers

namespace utils {
	
	/** Proxy object to allow [][] syntax when using JumpTables */
	template <typename jType, typename Value>
	class JumpRow {
	public:
		JumpRow(std::unordered_map<jType, Value>& row) : Row(&row) {

		}

		Value& operator[] (jType j);

		std::unordered_map<jType, Value>* Row;
	};

	template <typename iType, typename jType, typename Value>
	class JumpTable2D {
	public:

		/**
		 * Constructor
		 */
		JumpTable2D();

		/**
		 * Inserts an entry into the jump table
		 */
		void Insert(iType i, jType j, Value value);

		/**
		 * Removes entry from jump table
		 */
		void Erase(iType i, jType j);

		/**
		 * ArrayIndex operator overload
		 */
		JumpRow<jType, Value> operator[] (iType i);

		/**
		 * Find operator returns read only pointer to value in table
		 */
		const Value* Find(iType i, jType j) const;
		
	private:
		std::unordered_map<iType, std::unordered_map<jType, Value>> Table;
	};

	//JumpRow impl
	template<typename jType, typename Value>
	inline Value& JumpRow<jType, Value>::operator[] (jType j) {
		auto entryIter = Row->find(j);
		if (entryIter == Row->end()) {
			Value v;
			entryIter = Row->insert({ j, v }).first;
		}

		return entryIter->second;
	}

	//JumpTable impl
	template<typename iType, typename jType, typename Value>
	inline JumpTable2D<iType, jType, Value>::JumpTable2D() {
	}

	template<typename iType, typename jType, typename Value>
	inline void JumpTable2D<iType, jType, Value>::Insert(iType i, jType j, Value value) {
		Table[i][j] = value;
	}

	template<typename iType, typename jType, typename Value>
	inline void JumpTable2D<iType, jType, Value>::Erase(iType i, jType j) {
		auto row = Table.find(i);
		if (row == Table.end()) {
			return;
		}

		row->second.erase(j);
	}

	template<typename iType, typename jType, typename Value>
	inline JumpRow<jType, Value> JumpTable2D<iType, jType, Value>::operator[] (iType i) {
		auto rowIter = Table.find(i);

		if (rowIter == Table.end()) {
			std::unordered_map<jType, Value> newRow;
			rowIter = Table.insert({i, newRow}).first;
		}

		return JumpRow<jType, Value>(rowIter->second);
	}

	template<typename iType, typename jType, typename Value>
	inline const Value* JumpTable2D<iType, jType, Value>::Find(iType i, jType j) const {
		auto rowIter = Table.find(i);
		
		if (rowIter == Table.end()) {
			return nullptr;
		}

		auto entryIter = rowIter->second.find(j);
		if (entryIter == rowIter->second.end()) {
			return nullptr;
		}

		return &entryIter->second;
	}

}

