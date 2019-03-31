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
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
float xx = 0, yy = 0, zz = 0, x = 0.0f, y = 0.0f, z = 1.0f, x_1 = 0.0f, y_1 = 0.0f;
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";

void CreateObject()
{
	unsigned int indices[] = { 
		// front
		0, 1, 3,
		1, 2, 3,
		// right
		2, 4, 3,
		4, 5, 3,
		// left
		5, 6, 3,
		6, 0, 3,
		// bottom
		0, 1, 5,
		1, 2, 5
		/*
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2*/
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,//0
		0.0f,-0.5f,0.0f,//1
		0.5f,-0.5f, 0.0f,//2
		0.0f,0.5f,-0.5f,//3
		0.25f,-0.5f,-0.5f,//4
		0.0f,-0.5f,-1.0f,//5
		-0.25f,-0.5f,-0.5//6
	};
	//Instancia de la piramide
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj1);
	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj2);
	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj3);
	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj4);
	Mesh *obj5 = new Mesh();
	obj5->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj5);
	Mesh *obj6 = new Mesh();
	obj6->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj6);
	Mesh *obj7 = new Mesh();
	obj7->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj7);
	Mesh *obj8 = new Mesh();
	obj8->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj8);
	Mesh *obj9 = new Mesh();
	obj9->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj9);
	Mesh *obj10 = new Mesh();
	obj10->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj10);
	Mesh *obj11 = new Mesh();
	obj11->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj11);
	Mesh *obj12 = new Mesh();
	obj12->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj12);
	Mesh *obj13 = new Mesh();
	obj13->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj13);
	Mesh *obj14 = new Mesh();
	obj14->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj14);
	Mesh *obj15 = new Mesh();
	obj15->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj15);
	Mesh *obj16 = new Mesh();
	obj16->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj16);
	Mesh *obj17 = new Mesh();
	obj17->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj17);
	Mesh *obj18 = new Mesh();
	obj18->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj18);
	Mesh *obj19 = new Mesh();
	obj19->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj19);
	Mesh *obj20 = new Mesh();
	obj20->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj20);
	Mesh *obj21 = new Mesh();
	obj21->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj21);
	Mesh *obj22 = new Mesh();
	obj22->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj22);
	Mesh *obj23 = new Mesh();
	obj23->CreateMesh(vertices, indices, 24, 24);
	meshList.push_back(obj23);
}
//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 3,
		0, 1, 4,
		// right
		0, 4, 5,
		0, 5, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.0f, -0.0f,  0.0f,
	0.5f, 0.5f,  -0.25f,
	-0.5f,  0.5f,  -0.25f,
	0.5f,  0.0f,  -1.0f,
	// back
	-0.5f, 0.0f, -1.0f
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
	CreateObject();
	CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glm::mat4 view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(x_1, y_1, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		//model = glm::mat4(1.0);
		//Traslación
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//////////////// ROTACIÓN //////////////////
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////////////////  ESCALA ////////////////

		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		///////////////////// T+R////////////////
		/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		*/
		/////////////R+T//////////
		/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		*/

		//Primer nivel
		glm::mat4 model(1.0);
		glm::vec3 currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.8f, -0.8f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f,1.0f,0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model,glm::vec3(-0.3f, -0.8f, -0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 53 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.1f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[1]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, -0.8f, -0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[2]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.7f, -0.8f, -0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 53 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.1f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[3]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.0f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(1.2f, -0.8f, -0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.33f, 0.676f, 0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[16]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.3f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.7f, -0.8f, -1.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.12f, 0.0f, 0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.45f, -0.8f, -1.5f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[17]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.1f, 0.3f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, -0.8f, -2.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[6]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.676f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.05f, -0.8f, -1.5f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[18]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.7f, 0.1f, 0.3f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.3f, -0.8f, -1.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.33f, 0.676f, 0.11f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.55f, -0.8f, -0.5f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[19]->RenderMesh();

		//capa inferior
		//i1
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.1f, 0.7f, 0.1f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.3f, -0.8f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[8]->RenderMesh();

		//i2
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 0.5f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.7f, -0.8f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[9]->RenderMesh();

		//i3
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.1f, 0.2f, 0.3f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, -0.8f, -2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[10]->RenderMesh();
		
		//segundo nivel
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.3f, 0.2f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[11]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, 0.4f, -0.7f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 54 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.075f, 0.05f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[12]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.7f, 0.2f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[13]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.6f, 0.276f, 0.1f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.45f, 0.2f, -1.0f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[21]->RenderMesh();
		
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.122f, 0.44f, 1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, 0.2f, -1.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[14]->RenderMesh();

		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(1.00f, 0.276f, 0.111f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(-0.05f, 0.2f, -1.0f));
		//model = glm::translate(model, glm::vec3(0.95f, -0.8f, -0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.1f, -0.2f, 0.2f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[22]->RenderMesh();
		
		//tercer nivel
		model = glm::mat4(1.0);//reiniciamos modelo con la matriz identidad
		currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(0.2f, 1.2f, -1.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//ejercicio 1: repetir instancias del cubo o cuadrados para replicar una figura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(currentColor));
		meshList[15]->RenderMesh();
		
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}