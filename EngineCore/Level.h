#pragma once
//STD Headers


//Library Headers


//Coati Headers

namespace EngineCore {

	class Level {

	public:
		//CTORS
		Level(int levelID);
		~Level();

		//Accessors
		int GetName() const;

		//Tick function;
		void Tick();

	private:
		//Identifier for the Level, 1 will be basic world.
		int levelID;

	};

}