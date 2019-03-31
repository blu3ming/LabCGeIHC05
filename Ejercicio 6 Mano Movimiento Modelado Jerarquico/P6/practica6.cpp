
/*
Semestre 2019-2
Práctica 6 Modelado Jerárquico
Hecho por: Ing. José Roque Román Guadarrama
*/

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
const float toRadians = 3.14159265f/180.0; //grados a radianes
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float codo = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(1, 20, 20);

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
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		//ejercicio 1: Crear un brazo formado por hombro, brazo,codo, antebrazo, muñeca,palma, dedos.
		//hombro, codo y muñeca sólo son puntos de rotación o articulación, en este caso no dibujaremos esferas que los representen
		//Creando el hombro 
		glm::mat4 model(1.0);
		glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		glm::mat4 modeltemp(1.0);//guardara datos anteriores y actuales, translate y rotate
		//brazo
		model = glm::mat4(1.0);
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -1.7f));
		model = glm::rotate(model, glm::radians(mainWindow.gethombro() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		/*En caso de ser el codo una esfera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.15f, 0.0f, -1.7f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		*/

		//codo
		model = glm::translate(modeltemp, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcodo() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model;

		//antebrazo
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		modeltemp = model = glm::translate(modeltemp, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//muñeca
		model = glm::translate(modeltemp, glm::vec3(0.25f, 0.0f, 0.0f));
		modeltemp = model = glm::rotate(model, glm::radians(mainWindow.getmuneca() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//palma
		currentColor = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//dedo1
		//palma-falange	
		glm::mat4 modeltemp2(1.0);
		modeltemp2 = modeltemp;
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.2f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalange_indice() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falange dedo índice
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falange-falangina
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangina_indice() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangina dedo índice
		currentColor = glm::vec3(1.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falangina-falangeta
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangeta_indice() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangeta dedo índice
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.08f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//dedo2
		//palma-falange
		modeltemp2 = modeltemp;
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.07f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalange_indice2() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falange dedo índice
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falange-falangina
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangina_indice2() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangina dedo índice
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falangina-falangeta
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangeta_indice2() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangeta dedo índice
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.08f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//dedo3
		//palma-falange
		modeltemp2 = modeltemp;
		model = glm::translate(modeltemp2, glm::vec3(0.3f, -0.06f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalange_indice3() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falange dedo índice
		currentColor = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falange-falangina
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangina_indice3() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangina dedo índice
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//falangina-falangeta
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangeta_indice3() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangeta dedo índice
		currentColor = glm::vec3(1.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.08f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//dedo4
		//palma-falange
		modeltemp2 = modeltemp;
		model = glm::translate(modeltemp2, glm::vec3(0.3f, -0.19f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalange_indice4() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falange dedo índice
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		//falange-falangina
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangina_indice4() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangina dedo índice
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		//falangina-falangeta
		model = glm::translate(modeltemp2, glm::vec3(0.3f, 0.0f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangeta_indice4() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangeta dedo índice
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.08f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//PULGAR
		//palma-falange
		modeltemp2 = modeltemp;
		model = glm::translate(modeltemp2, glm::vec3(0.18f, 0.25f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalange_indice5() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falange dedo índice
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();
		
		//falange-falangina
		model = glm::translate(modeltemp2, glm::vec3(0.0f, -0.3f, 0.0f));
		modeltemp2 = model = glm::rotate(model, glm::radians(mainWindow.getfalangeta_indice5() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));

		//falangina dedo índice
		currentColor = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}