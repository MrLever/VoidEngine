#pragma once
//STD Headers
#include <memory>

//Library Headers


//Forward Class declarations
class WindowManager;

class Renderer{
private:
	//Private class members
	std::shared_ptr<WindowManager> Window;

public:
	//CTORS
	Renderer(std::shared_ptr<WindowManager> Window);
	~Renderer();

private:
	//Private member functions


public:
	//Public member functions
	void Render();

};

