#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
#include "Window.h"
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
float x = 0.0f, y = 0.0f, z = 1.0f, x_1=0.0f, y_1=0.0f;
float colorx1 = 0.3f, colory1 = 1.0f, colorz1 = 0.2f;
float colorx2 = 0.2f, colory2 = 0.2f, colorz2 = 0.7f;
float colorx3 = 0.7f, colory3 = 0.3f, colorz3 = 0.9f;
float colorx4 = 0.5f, colory4 = 0.5f, colorz4 = 0.3f;
float colorx5 = 0.4f, colory5 = 0.2f, colorz5 = 1.0f;
float colorx6 = 0.4f, colory6 = 0.5f, colorz6 = 1.0f;
float colorx7 = 0.8f, colory7 = 0.8f, colorz7 = 0.6f;
float colorx8 = 0.9f, colory8 = 0.9f, colorz8 = 0.4f;
void CreateObject()
{
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,
		0.0f,-0.5f,0.5f,
		0.5f,-0.5f, 0.0f,
		0.0f,0.5f,0.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}
//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f, colorx1, colory1, colorz1,
	0.5f, -0.5f,  0.5f, colorx2, colory2, colorz2,
	0.5f,  0.5f,  0.5f, colorx3, colory3, colorz3,
	-0.5f,  0.5f,  0.5f, colorx4, colory4, colorz4,
	// back
	-0.5f, -0.5f, -0.5f, colorx5, colory5, colorz5,
	0.5f, -0.5f, -0.5f, colorx6, colory6, colorz6,
	0.5f,  0.5f, -0.5f, colorx7, colory7, colorz7,
	-0.5f,  0.5f, -0.5f, colorx8, colory8, colorz8,
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,48,72);
meshList.push_back(cubo);

}
void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//CreateObject();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f),
		mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),
		0.1f, 100.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(izq, izq, izq), glm::vec3(0.0f, 1.0f, 0.0f));//donde esta posicionada la camara, 
	//printf("%f", izq);																										   //hacia donde quiero ver (centro del cubo)
																													   //Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		CrearCubo();
		CreateShaders();
		mainWindow.createCallbacks();
		glm::mat4 view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(x_1, y_1, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		glm::mat4 model(1.0);
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));//2.5 DE PROFUNDIDAD EN LA VENTANA
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[0]->RenderMesh();
		//ejercicio 2: repetir instancias del cubo o cuardados para replicar una figura
		glUseProgram(0);
		meshList.pop_back();
		mainWindow.swapBuffers();
		//670
	}
	return 0;
}