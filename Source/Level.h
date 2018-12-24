#pragma once
//STD Headers


//Library Headers


//Coati Headers


class Level {

public:
	//CTORS
	Level(int levelID);
	~Level();

	//Accessors
	int GetID();

	//Tick function;
	void Tick();

private:
	//Identifier for the Level, 1 will be basic world.
	int levelID;

};