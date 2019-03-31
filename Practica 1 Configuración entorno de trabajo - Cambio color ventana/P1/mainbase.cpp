#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

int main()
{
	int cont = 0;
	float r, g, b;
	srand(time(NULL));
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	//glfw crea la ventana, la renderiza, y permite manejar interfaces(teclado y mouse, y monitor) OpenGL no las puede emplear sola.
	//glew maneja experimentales (retrocompatibilidad)
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n", glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		//permite hacer el emanejo de eventos, por medio de interfaces
		glfwPollEvents();

		//Limpiar la ventana
		//el bufer de color se limpia, y se le da este valor (r,g,b,alpha(siempre va a ser 1 para que se vea el color
		//(para shadders y texturizado varia de 0 a 1)))
		while (cont != 50000000) {
			cont += 1;
		}

		if (cont == 50000000) {
			r = rand() % 2;
			g = rand() % 2;
			b = rand() % 2;
			glClearColor(r, g, b, 1.0f);
			cont = 0;
		}
		//glClearColor(0.96f,0.0f,0.5294f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//
		glfwSwapBuffers(mainWindow);

	}


	return 0;
}