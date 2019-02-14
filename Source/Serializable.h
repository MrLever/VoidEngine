//STD Headers
#include <string>
#include <fstream>

//Library Headers



//Coati Headers


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
	virtual bool Save() { return false; }
	virtual bool Load() { return false; }




};