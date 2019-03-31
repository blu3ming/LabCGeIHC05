#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	//initialice glfw
	if (!glfwInit())
	{
		printf("glfw initialization failed");
		glfwTerminate();
		return 1;
	}

	//setup glfw window properties
	//opengl version
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//CORE PROFILE=NO BACKWARDS COMPATIBILITY
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TYPE);

	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit()!=GLEW_OK)
	{
		printf("glew initialization failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//setup viewport size
	glViewport(0,0,bufferWidth, bufferHeight);

	//loop untill window close
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();

		//clear window
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}