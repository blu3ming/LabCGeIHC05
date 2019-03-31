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
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getcodo() { return codo; }
	GLfloat gethombro() { return hombro; }
	GLfloat getmuneca() { return muneca; }
	GLfloat getfalange_indice() { return falange_indice; }
	GLfloat getfalange_indice2() { return falange_indice2; }
	GLfloat getfalange_indice3() { return falange_indice3; }
	GLfloat getfalange_indice4() { return falange_indice4; }
	GLfloat getfalange_indice5() { return falange_indice5; }
	GLfloat getfalangina_indice() { return falangina_indice; }
	GLfloat getfalangina_indice2() { return falangina_indice2; }
	GLfloat getfalangina_indice3() { return falangina_indice3; }
	GLfloat getfalangina_indice4() { return falangina_indice4; }
	GLfloat getfalangeta_indice() { return falangeta_indice; }
	GLfloat getfalangeta_indice2() { return falangeta_indice2; }
	GLfloat getfalangeta_indice3() { return falangeta_indice3; }
	GLfloat getfalangeta_indice4() { return falangeta_indice4; }
	GLfloat getfalangeta_indice5() { return falangeta_indice5; }
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat codo,hombro,muneca, falange_indice, falange_indice2, falange_indice3, falange_indice4, falange_indice5,
		falangina_indice, falangina_indice2, falangina_indice3, falangina_indice4,
		falangeta_indice, falangeta_indice2, falangeta_indice3, falangeta_indice4, falangeta_indice5=-90.0f;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
};

