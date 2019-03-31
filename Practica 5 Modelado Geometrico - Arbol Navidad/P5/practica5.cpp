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
		while (cont != 50000000) {
			cont += 1;
		}

		if (cont == 50000000) {
			colorx1 = (float)rand() / RAND_MAX; colory1 = (float)rand() / RAND_MAX; colorz1 = (float)rand() / RAND_MAX;
			colorx2 = (float)rand() / RAND_MAX; colory2 = (float)rand() / RAND_MAX; colorz2 = (float)rand() / RAND_MAX;
			colorx3 = (float)rand() / RAND_MAX; colory3 = (float)rand() / RAND_MAX; colorz3 = (float)rand() / RAND_MAX;
			colorx4 = (float)rand() / RAND_MAX; colory4 = (float)rand() / RAND_MAX; colorz4 = (float)rand() / RAND_MAX;
			colorx5 = (float)rand() / RAND_MAX; colory5 = (float)rand() / RAND_MAX; colorz5 = (float)rand() / RAND_MAX;
			colorx6 = (float)rand() / RAND_MAX; colory6 = (float)rand() / RAND_MAX; colorz6 = (float)rand() / RAND_MAX;
			colorx7 = (float)rand() / RAND_MAX; colory7 = (float)rand() / RAND_MAX; colorz7 = (float)rand() / RAND_MAX;
			colorx8 = (float)rand() / RAND_MAX; colory8 = (float)rand() / RAND_MAX; colorz8 = (float)rand() / RAND_MAX;
			cont = 0;
		}
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
		
		//Estrella
		glm::mat4 model(1.0); 
		glm::vec3 currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.35f, -2.5f));
		model = glm::scale(model, glm::vec3(0.9, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshListEstrella[0]->RenderMesh();

		//1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f,0.0f,0.0f);
		model = glm::translate(model, glm::vec3(-0.43f, 0.18f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.43f, 0.18f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.18f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.47f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.20f, 0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.20f, 0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//7
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.15f, 0.08f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//8
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.08f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//9
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.29f, -0.02f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//10
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.02f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//11
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.29f, -0.02f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//12
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.52f, -0.14f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//13
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.52f, -0.14f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//14
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.15f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//15
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.15f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//16
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.29f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//17
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//18
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.29f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//19
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.43f, -0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//20
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//21
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//22
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.43f, -0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//23
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.64f, -0.47f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//24
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.64f, -0.47f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//25
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//linea 1 - luces
		//luz1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(-0.2f, 0.42f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.17f, 0.41f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.14f, 0.4f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.11f, 0.39f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(-0.08f, 0.38f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
		//luz6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(-0.05f, 0.37f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz7
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(-0.02f, 0.36f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz8
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.01f, 0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz9
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.04f, 0.34f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz10
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.07f, 0.33f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz11
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.1f, 0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz12
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.13f, 0.31f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz13
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(0.16f, 0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz14
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(0.19f, 0.29f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz15
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(0.22f, 0.28f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz16
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.25f, 0.27f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz17
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.28f, 0.26f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz18
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.31f, 0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz19
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.34f, 0.24f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz20
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.37f, 0.23f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//linea 2 - luces
		//luz1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(-0.2f, 0.17f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.17f, 0.16f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.14f, 0.15f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.11f, 0.14f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(-0.08f, 0.13f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(-0.05f, 0.12f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz7
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(-0.02f, 0.11f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz8
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.01f, 0.10f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz9
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.04f, 0.09f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz10
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.07f, 0.08f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz11
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.1f, 0.07f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz12
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.13f, 0.06f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz13
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(0.16f, 0.05f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz14
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(0.19f, 0.04f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz15
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(0.22f, 0.03f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz16
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.25f, 0.02f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz17
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.28f, 0.01f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz18
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.31f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz19
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.34f, -0.01f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz20
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.37f, -0.02f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz21
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(0.4f, -0.03f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz22
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(0.43f, -0.04f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//linea 3 - luces
		//luz-6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.41f, -0.03f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.38f, -0.04f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.35f, -0.05f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(-0.32f, -0.06f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(-0.29f, -0.07f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(-0.26f, -0.08f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz0
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(-0.23f, -0.09f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(-0.2f, -0.1f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.17f, -0.11f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.14f, -0.12f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.11f, -0.13f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(-0.08f, -0.14f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(-0.05f, -0.15f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz7
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(-0.02f, -0.16f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz8
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.01f, -0.17f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz9
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.04f, -0.18f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz10
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.07f, -0.19f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz11
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.1f, -0.2f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz12
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.13f, -0.21f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz13
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(0.16f, -0.22f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz14
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(0.19f, -0.23f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz15
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(0.22f, -0.24f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz16
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.25f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz17
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.28f, -0.26f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz18
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(0.31f, -0.27f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz19
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(0.34f, -0.28f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz20
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(0.37f, -0.29f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz21
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(0.4f, -0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz22
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(0.43f, -0.31f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz23
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(0.46f, -0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz24
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(0.49f, -0.33f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz25
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(0.52f, -0.34f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//linea 4 - luces
		//luz-8
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(-0.47f, -0.29f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-7
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(-0.44f, -0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-6
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.41f, -0.31f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-5
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.38f, -0.32f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.35f, -0.33f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx5, colory5, colorz5);
		model = glm::translate(model, glm::vec3(-0.32f, -0.34f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx6, colory6, colorz6);
		model = glm::translate(model, glm::vec3(-0.29f, -0.35f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz-1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx7, colory7, colorz7);
		model = glm::translate(model, glm::vec3(-0.26f, -0.36f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz0
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx8, colory8, colorz8);
		model = glm::translate(model, glm::vec3(-0.23f, -0.37f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx1, colory1, colorz1);
		model = glm::translate(model, glm::vec3(-0.20f, -0.38f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx2, colory2, colorz2);
		model = glm::translate(model, glm::vec3(-0.17f, -0.39f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx3, colory3, colorz3);
		model = glm::translate(model, glm::vec3(-0.14f, -0.4f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();

		//luz4
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(colorx4, colory4, colorz4);
		model = glm::translate(model, glm::vec3(-0.11f, -0.41f, -1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		sp.render();
		
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
		currentColor = glm::vec3(0.0f, 0.5f,1.0f);
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
		currentColor = glm::vec3(0.0f, 0.5f,1.0f);
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

		//Arbol parte superior
		//meshList[0]->RenderMesh();
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.45f, -2.5f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//arbol parte media
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -2.5f));
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[1]->RenderMesh();

		//arbol parte baja
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, -2.5f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[2]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}