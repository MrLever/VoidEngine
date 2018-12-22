#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
};

