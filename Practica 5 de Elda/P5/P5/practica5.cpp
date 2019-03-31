#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include "Sphere.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(1.0, 20, 20);

void CreateObject()
{
	unsigned int indices[] = {
		0,1,2
	};

	GLfloat vertices[] = {
		-1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		0.0,1.0f,0.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices ,12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices,12, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(vertices, indices ,12, 12);
	meshList.push_back(obj3);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vertices, indices,12, 12);
	meshList.push_back(obj4);

	Mesh *obj5 = new Mesh();
	obj5->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj5);

	Mesh *obj6 = new Mesh();
	obj6->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj6);

	Mesh *obj7 = new Mesh();
	obj7->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj7);

	Mesh *obj8 = new Mesh();
	obj8->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj8);

	Mesh *obj9 = new Mesh();
	obj9->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj9);

	Mesh *obj10 = new Mesh();
	obj10->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj10);
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
	CreateObject();
	//CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glm::mat4 model(1.0);
		glm::vec3 currentColor = glm::vec3/*(1.0f, 1.0f, 1.0f);*/(0.0f, 0.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		glm::mat4 modeltemp(1.0);
		glm::mat4 modeltemp2(1.0);
		model = glm::translate(model, glm::vec3(0.5f, -0.2f, -4.1f));
		modeltemp = model;

		//ESFERA IRIS
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.0f, -0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//esfera OJO
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.0f, -0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//CUERPO PEZ
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.4f, -0.3f, -1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.gethombro() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;

		currentColor = glm::vec3(0.95f, 0.47f, 0.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(-0.0f, -0.0f, -0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//	TRIANGULO 1 CUERPO PEZ

		
		currentColor = glm::vec3(0.95f, 0.12f, 0.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.0f, -0.0f, -0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[1]->RenderMesh();

		//	TRIANGULO 2 CUERPO PEZ

		currentColor = glm::vec3(0.96f, 0.66f, 0.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(-0.4f, 0.3f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[2]->RenderMesh();

		model = glm::translate(model, glm::vec3(1.5f, -0.00f, -1.0f));
		modeltemp = model;
		//Triangulo 3 ALETA ATRAS

		currentColor = glm::vec3(0.95f, 0.12f, 0.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(-0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[3]->RenderMesh();

		//Triangulo 4 ALETA ATRAS AMARILLO

		currentColor = glm::vec3(0.88f, 0.95f, 0.0f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.3f, -0.05f, -1.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[4]->RenderMesh();

		
		//esfera burbuja PEZ 1

		model = glm::translate(model, glm::vec3(-2.0f, 3.5f, -1.0f));
		modeltemp = model;

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.8f, 0.1f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//esfera burbuja PEZ 1
		model = glm::translate(model, glm::vec3(2.9f, 1.5f, -1.0f));
		modeltemp = model;

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.7f, -0.1f, -1.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//esfera burbuja PEZ 1
		model = glm::translate(model, glm::vec3(-8.9f, 0.0f, -1.0f));
		modeltemp = model;

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp = glm::translate(modeltemp, glm::vec3(0.8f, 0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();



		/*ESFERA OJO IRIS PEZ 1*/
		model = glm::mat4(1.0);
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, -1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.gethombro() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render(); 

		/*ESFERA OJO PEZ 1*/
		model = glm::mat4(1.0);
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.36f, 0.4f, -1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcodo() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp2 = model;
		//TRIANGULO ALETA MORADA

		currentColor = glm::vec3(0.34f, 0.13f, 0.39f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.38f, -0.3f, -1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(-0.0f, -0.2f, -1.0f));
		modeltemp2 = model;

		//TRIANGULO 5 CUERPO AMARILLO
		currentColor = glm::vec3(0.88f, 0.95f, 0.0f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.4f, 0.4f, -1.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[6]->RenderMesh();


		model = glm::translate(model, glm::vec3(-0.0f, -0.0f, -1.0f));
		modeltemp2 = model;
		//TRIANGULO 6 CUERPO MORADO

		currentColor = glm::vec3(0.34f, 0.13f, 0.39f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.4f, 0.4f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[7]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.39f, -0.98f, -1.0f));
		modeltemp2 = model;

		//TRINGULO ALETA AMARILLA
		currentColor = glm::vec3(0.99f, 0.84f, 0.0f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.55f, -0.08f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[8]->RenderMesh();

		//TRIANGULO AMARILLO ALETA 

		model = glm::translate(model, glm::vec3(1.69f, -0.0f, -1.0f));
		modeltemp2 = model;

		currentColor = glm::vec3(0.99f, 0.84f, 0.0f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.55f, -0.08f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[9]->RenderMesh();

		
		/********************************/
		model = glm::translate(model, glm::vec3(-0.9f, -6.0f, -1.0f));
		modeltemp2 = model;
		//esfera burbuja PEZ 2

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.8f, 0.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//esfera burbuja PEZ 2
		model = glm::translate(model, glm::vec3(-2.0f, 2.0f, -1.0f));
		modeltemp2 = model;

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.7f, 0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//esfera burbuja PEZ 2
		model = glm::translate(model, glm::vec3(-2.0f, -2.0f, -1.0f));
		modeltemp2 = model;

		currentColor = glm::vec3(0.33f, 0.39f, 0.92f);
		modeltemp2 = glm::translate(modeltemp2, glm::vec3(-0.8f, 0.7f, -1.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		/*ESFERAS BURBUJAS ESPECIALES*/

		model = glm::mat4(1.0);
		currentColor = glm::vec3(0.03f, 0.25f, 0.57f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}