#include "Window.h"
#include<stdlib.h>
#include<time.h>

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)//recibir las teclas del teclado
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)//valores enteros a queubique en la ventana
{
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica 3", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();//callbacks:eventos


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);//esperamosa que el usuario etse en la ventana y ubique el puntero del usuario, 
	//no de mouse, sino que el usuario se enfoca en esa ventana
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);//comando para detectar teclado (glfw)
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)//MODE-MODIFICADORES (CTRL, ALT, SHIFT), FUNCIONAN EN CONJUNTO CON PTRA TECLA
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//recibe la tecla, PRESS O RELEASE
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n",key_name);
		x -= 0.1f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y -= 0.1f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		x += 0.1f;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y += 0.1f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		x_1 -= 0.1f;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		x_1 += 0.1f;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y_1 -= 0.1f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y_1 += 0.1f;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z -= 0.1f;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z += 0.1f;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
		colorx1 = (float)rand()/RAND_MAX; colory1 = (float)rand()/RAND_MAX; colorz1 = (float)rand()/RAND_MAX;
		colorx2 = (float)rand()/RAND_MAX; colory2 = (float)rand()/RAND_MAX; colorz2 = (float)rand()/RAND_MAX;
		colorx3 = (float)rand()/RAND_MAX; colory3 = (float)rand()/RAND_MAX; colorz3 = (float)rand()/RAND_MAX;
		colorx4 = (float)rand()/RAND_MAX; colory4 = (float)rand()/RAND_MAX; colorz4 = (float)rand()/RAND_MAX;
		colorx5 = (float)rand()/RAND_MAX; colory5 = (float)rand()/RAND_MAX; colorz5 = (float)rand()/RAND_MAX;
		colorx6 = (float)rand()/RAND_MAX; colory6 = (float)rand()/RAND_MAX; colorz6 = (float)rand()/RAND_MAX;
		colorx7 = (float)rand()/RAND_MAX; colory7 = (float)rand()/RAND_MAX; colorz7 = (float)rand()/RAND_MAX;
		colorx8 = (float)rand()/RAND_MAX; colory8 = (float)rand()/RAND_MAX; colorz8 = (float)rand()/RAND_MAX;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("se solto la tecla %d'\n", key);
		}
	}
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
