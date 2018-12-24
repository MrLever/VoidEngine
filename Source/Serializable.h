//STD Headers
#include <string>


//Library Headers



//Coati Headers



class Serializable {

public:

	virtual void Save(std::string Filepath) = 0;
	virtual void Load(std::string Filepath) = 0;

private:



};