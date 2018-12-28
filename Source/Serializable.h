//STD Headers
#include <string>


//Library Headers



//Coati Headers



class Serializable {

private:
	//Private class members
	std::string FilePath;
public:
	//CTORS
	Serializable(std::string targetFilepath);
	~Serializable();

public:
	//Public Member Functions
	virtual void Save() = 0;
	virtual void Load() = 0;

private:
	//Private Member Functions


};