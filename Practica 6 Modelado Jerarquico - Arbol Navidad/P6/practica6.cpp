#include <stdio.h>
#include <string.h>
#include <time.h>
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
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
int cont=0;
float colorx1 = 0.3f, colory1 = 1.0f, colorz1 = 0.2f;
float colorx2 = 0.2f, colory2 = 0.2f, colorz2 = 0.7f;
float colorx3 = 0.7f, colory3 = 0.3f, colorz3 = 0.9f;
float colorx4 = 0.5f, colory4 = 0.5f, colorz4 = 0.3f;
float colorx5 = 0.4f, colory5 = 0.2f, colorz5 = 1.0f;
float colorx6 = 0.4f, colory6 = 0.5f, colorz6 = 1.0f;
float colorx7 = 0.8f, colory7 = 0.8f, colorz7 = 0.6f;
float colorx8 = 0.9f, colory8 = 0.9f, colorz8 = 0.4f;
std::vector<Mesh*> meshList;
std::vector<Mesh*> meshListCubo;
std::vector<Mesh*> meshListEstrella;
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
		-1.0f, 0.0f,0.0f,
		1.0f,0.0f,0.0f,
		0.0f,0.8660254f, 0.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj3);
	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj4);
}

void CreateEstrella()
{
	unsigned int indices[] = {

		0,1,2,
		1,3,5,
		2,4,6,
		1,6,2,
		1,5,6,
		5,6,8,
		5,7,8,
		6,9,8
	};
	GLfloat vertices[] = {
		0.0f, 0.22f,0.0f,
		-0.08f,0.08f,0.0f,
		0.08f,0.08f,0.0f,
		-0.24f,0.05f,0.0f,
		0.24f,0.05f,0.0f,
		-0.12f,-0.05f,0.0f,
		0.12f,-0.05f,0.0f,
		-0.15f,-0.23f,0.0f,
		0.0f,-0.15f,0.0f,
		0.15f,-0.23f,0.0f
	};
	Mesh *estrella = new Mesh();
	estrella->CreateMesh(vertices, indices, 36, 36);
	meshListEstrella.push_back(estrella);
}
//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		1,3,2
	};

GLfloat cubo_vertices[] = {
	-0.5f, 0.0f,  0.0f,
	0.0f, 0.0f,  0.0f,
	-0.5f,  0.5f,  0.0f,
	0.0f,  0.5f,  0.0f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshListCubo.push_back(cubo);

Mesh *cubo1 = new Mesh();
cubo1->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo1);

Mesh *cubo2 = new Mesh();
cubo2->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo2);

Mesh *cubo3 = new Mesh();
cubo3->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo3);

Mesh *cubo4 = new Mesh();
cubo4->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo4);

Mesh *cubo5 = new Mesh();
cubo5->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo5);

Mesh *cubo6 = new Mesh();
cubo6->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo6);

Mesh *cubo7 = new Mesh();
cubo7->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo7);

Mesh *cubo8 = new Mesh();
cubo8->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo8);

Mesh *cubo9 = new Mesh();
cubo9->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo9);

Mesh *cubo10 = new Mesh();
cubo10->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
meshListCubo.push_back(cubo10);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	srand(time(NULL));
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreateEstrella();
	CreateObject();
	CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Loop mientras no se cierra la ventana

	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.5f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//giro parte baja
		glm::mat4 model(1.0); 
		glm::vec3 currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		glm::mat4 modeltemp(1.0);//guardara datos anteriores y actuales, translate y rotate
		//parte baja
		model = glm::mat4(1.0);
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.65f, -1.75f));
		model = glm::rotate(model, glm::radians(mainWindow.gethombro() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();
		
		//1
		//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.2f, 0.15f, 0.1f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//2
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.43f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//3
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.83f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//4
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.43f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//5
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.4f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//6
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-2.06f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//7
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.62f, 0.35f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//8
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.42f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//9
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.42f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//10
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.22f, 0.15f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//11
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.42f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//giro medio
		model = glm::translate(modeltemp, glm::vec3(0.22f, 0.1f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcodo() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;

		//medio
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[1]->RenderMesh();

		//12
		//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.0f, 0.12f, 0.1f));
		model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//13
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.39f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//14
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.78f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//15
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.32f, -0.15f, 0.1f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//16
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(1.4f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//17
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.54f, 0.26f, 0.1f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//18
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.29f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.055f, 0.055f, 0.055f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//19
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.14f, 0.08f, 0.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//giro alto
		model = glm::translate(modeltemp, glm::vec3(0.0f, 0.02f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcodo2() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;

		//alto
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.42f, 0.42f, 0.42f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[1]->RenderMesh();

		//20
		//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.0f, 0.09f, 0.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//21
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.16f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//22
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.32f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//23
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.22f, -0.15f, 0.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//24
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.76f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//25
		//reiniciamos modelo con la matriz identidad
		modeltemp = model = glm::translate(modeltemp, glm::vec3(-0.38f, 0.28f, 0.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//Estrella eje
		model = glm::translate(modeltemp, glm::vec3(0.0f, 0.14f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcodo3() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;

		//estrella
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.42f, 0.42f, 0.42f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListEstrella[0]->RenderMesh();
		
		//base tronco
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.4f, 0.1f, 0.0f);
		model = glm::translate(model, glm::vec3(0.17f, -1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListCubo[0]->RenderMesh();

		//regalo izq
		//moño izq negro
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.5f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.28f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.022f, 0.022f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño izq
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.28f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño der negro
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.5f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.21f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.022f, 0.022f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño der
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.21f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//liston
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.44f, -1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.2, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListCubo[1]->RenderMesh();

		//caja
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.7f, 0.2f, 0.3f);
		model = glm::translate(model, glm::vec3(-0.3f, -1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.8, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListCubo[2]->RenderMesh();

		//regado der
		//moño izq negro
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.5f, 1.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.022f, 0.022f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño izq
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño der negro
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.5f, 1.0f);
		model = glm::translate(model, glm::vec3(0.27f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.022f, 0.022f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//moño der
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.27f, -0.46f, -1.0f));
		model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//liston
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.52f, -1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.2, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListCubo[3]->RenderMesh();

		//caja
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.67f, -1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.8, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListCubo[4]->RenderMesh();
		
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}