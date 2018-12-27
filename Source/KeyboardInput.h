#pragma once
//STD Headers


//Library Headers


//Forward Class declarations

enum KeyType {
	INPUT_ESC = 256,
	INPUT_W = 87,
	INPUT_A = 65,
	INPUT_S = 83,
	INPUT_D = 68,
	INPUT_NUM_9 = 329
};

enum KeyState {
	Pressed = 1,
	Held,
	Released
};

class KeyboardInput {
private:
	//Private Class Members
	KeyType Key;
	KeyState State;
public:
	//CTORS
	KeyboardInput(KeyType Key, KeyState State);
	~KeyboardInput();

private:

public:
	KeyType GetKey();
	KeyState GetKeyState();

};

