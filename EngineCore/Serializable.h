#pragma once

//STD Headers
#include <string>
#include <fstream>

//Library Headers



//Coati Headers

namespace utils {

	class Serializable {

	private:
		//Private class members



	protected:
		//Protected class members
		std::string FilePath;

	public:
		//CTORS
		Serializable(std::string targetFilepath);
		~Serializable();

	private:
		//Private Member Functions

	protected:
		//Protected Member Functions

	public:
		//Public Member Functions
		virtual bool Save() const = 0;
		virtual bool Load() = 0;
	};

}