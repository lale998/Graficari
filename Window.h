#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>

class Window
{
private:
	GLFWwindow* m_window;
	int  m_height, m_width;
	int  m_initPosX, m_initPosY;
	bool m_fullsc;
	
	void resize(int, int);
	static void resizeCallback(GLFWwindow*, int, int);
	static void key_callback(GLFWwindow*, int, int, int, int);
	

public:
	Window(const int, const int, const std::string&,bool);

	int         getHeight(void)	    { return m_height; }
	int         getWidth(void)		{ return m_width;  }
	bool        isFullScreen(void)  { return m_fullsc; }
	GLFWwindow* getWindow(void)     { return m_window; }

	void setFullScreen(bool);

	~Window();
};