#pragma once
//STD Headers
#include <unordered_map>

//Library Headers

//Void Engine Headers

namespace utils {
	
	/** Proxy object to allow [][] syntax when using JumpTables */
	template <typename jType, typename Value>
	class TableRow {
	public:
		TableRow(std::unordered_map<jType, Value>& row) : Row(&row) {

		}

		Value& operator[] (jType j);

		std::unordered_map<jType, Value>* Row;
	};

	template <typename iType, typename jType, typename Value>
	class Table {
	public:

		/**
		 * Constructor
		 */
		Table();

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
		TableRow<jType, Value> operator[] (iType i);

		/**
		 * Find operator returns read only pointer to value in table
		 */
		const Value* Find(iType i, jType j) const;
		
	private:
		std::unordered_map<iType, std::unordered_map<jType, Value>> UnorderedTable;
	};

	//TableRow impl
	template<typename jType, typename Value>
	inline Value& TableRow<jType, Value>::operator[] (jType j) {
		auto entryIter = Row->find(j);
		if (entryIter == Row->end()) {
			Value v;
			entryIter = Row->insert({ j, v }).first;
		}

		return entryIter->second;
	}

	//JumpTable impl
	template<typename iType, typename jType, typename Value>
	inline Table<iType, jType, Value>::Table() {
	}

	template<typename iType, typename jType, typename Value>
	inline void Table<iType, jType, Value>::Insert(iType i, jType j, Value value) {
		UnorderedTable[i][j] = value;
	}

	template<typename iType, typename jType, typename Value>
	inline void Table<iType, jType, Value>::Erase(iType i, jType j) {
		auto row = UnorderedTable.find(i);
		if (row == UnorderedTable.end()) {
			return;
		}

		row->second.erase(j);
	}

	template<typename iType, typename jType, typename Value>
	inline TableRow<jType, Value> Table<iType, jType, Value>::operator[] (iType i) {
		auto rowIter = UnorderedTable.find(i);

		if (rowIter == UnorderedTable.end()) {
			std::unordered_map<jType, Value> newRow;
			rowIter = UnorderedTable.insert({i, newRow}).first;
		}

		return TableRow<jType, Value>(rowIter->second);
	}

	template<typename iType, typename jType, typename Value>
	inline const Value* Table<iType, jType, Value>::Find(iType i, jType j) const {
		auto rowIter = UnorderedTable.find(i);
		
		if (rowIter == UnorderedTable.end()) {
			return nullptr;
		}

		auto entryIter = rowIter->second.find(j);
		if (entryIter == rowIter->second.end()) {
			return nullptr;
		}

		return &entryIter->second;
	}

}

