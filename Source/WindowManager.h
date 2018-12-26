#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "InputManager.h"

//Forward Class declarations


class WindowManager {

private:
	//Private class members
	std::shared_ptr<GLFWwindow> Window;
	std::string GameName;

public:
	//CTORS
	WindowManager(std::string GameName);
	~WindowManager();

private:
	//Private member functions
	void InitGLFW();
	void InitGLAD();

public:
	//Public member functions
	std::shared_ptr<GLFWwindow> getWindow();

	void SwapBuffers();
	void PollInput();
	bool WindowTerminated();

	template<typename T>
	void SetWindowUser(T* requester) {
		glfwSetWindowUserPointer(Window.get(), requester);
	}

	

public:
	//Static Functions
	static void DeleteWindow(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}

	//std::shared_ptr<SDL_Surface>(SDL_LoadBMP(....), DeleteSurface);
	static void ReportWindowError(int error, const char* description) {
		std::cerr << "Error: " << description << std::endl;
	}

	static void ResizeFrameBuffer(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	static void DispatchKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//std::cout << "Callback triggered\n";
		InputManager* ptr = reinterpret_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (ptr) {
			KeyState state;
			if (action == GLFW_PRESS) {
				state = Pressed;
			}
			else if (action == GLFW_REPEAT) {
				state = Held;
			}
			else {
				state = Released;
			}
			ptr->HandleInput(key, state);
		}
	}
};

