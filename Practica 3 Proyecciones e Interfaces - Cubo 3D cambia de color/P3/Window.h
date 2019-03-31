#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>
extern float x, y, z, x_1, y_1, z_pos, z_neg;
extern float colorx1, colory1, colorz1;
extern float colorx2, colory2, colorz2;
extern float colorx3, colory3, colorz3;
extern float colorx4, colory4, colorz4;
extern float colorx5, colory5, colorz5;
extern float colorx6, colory6, colorz6;
extern float colorx7, colory7, colorz7;
extern float colorx8, colory8, colorz8;
class Window
{
public:
	//parametros para declarar la ventana
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {//cuando detecta que queremos cerrar la ventana
		return  glfwWindowShouldClose(mainWindow);}//Al presionar esc se cierra la ventana
	bool* getsKeys() { return keys; }//recibe info de presionado del teclado
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	void createCallbacks();
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);//
};

