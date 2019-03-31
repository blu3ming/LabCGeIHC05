#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getcodo() { return codo; }
	GLfloat gethombro() { return hombro; }
	GLfloat getmuneca() { return muneca; }
	GLfloat getfalange_indice() { return falange_indice; }
	GLfloat getfalangina_indice() { return falangina_indice; }
	GLfloat getfalangeta_indice() { return falangeta_indice; }
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat codo,hombro,muneca, falange_indice, falangina_indice, falangeta_indice;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

