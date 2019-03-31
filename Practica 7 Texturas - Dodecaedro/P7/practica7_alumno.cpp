/*
Semestre 2019-2
Práctica 7 Texturizado
Hecho por: Ing. José Roque Román Guadarrama. Usando librería stb_image.h 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

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
#include"Mesh_texturizado.h"
#include"Shader.h"
#include "Sphere.h"
#include"Window.h"
#include "Camera.h"
#include"Texture.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float codo = 0.0f;

Texture T_ladrillos;
Texture T_asfalto;
Texture T_dado;
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";
Sphere sp = Sphere(1, 20, 20);


//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		//1
		0,3,4,
		0,1,3,
		1,2,3,
		//2
		5,6,9,
		6,7,9,
		7,8,9,
		//3
		10,11,14,
		12,13,14,
		11,12,14,
		//4
		17,16,18,
		16,15,18,
		15,19,18,
		//5
		23,22,24,
		22,21,24,
		21,20,24,
		//6
		27,29,28,
		27,29,26,
		26,25,29,
		//7
		30,31,32,
		32,30,33,
		30,33,34,
		//8
		35,36,39,
		36,39,37,
		37,39,38,
		//9
		41,42,43,
		41,43,40,
		40,43,44,
		//10
		47,48,49,
		47,46,49,
		45,46,49,
		45,46,49,
		//11
		50,51,54,
		51,52,54,
		52,53,54,
		//12
		55,56,59,
		56,57,59,
		57,58,59
	};

GLfloat cubo_vertices[] = {
	//1
	//x		y		z								u		v
	1.0f, -1.0f,  1.0f,								0.002f,	0.002f,//0
	1.6180339887, -1.0/1.6180339887f,  0.0f,		0.25f,	0.002f,//1
	1.6180339887, 1.0/1.6180339887f,  0.0f,			0.37f,	0.33f,//2
	1.0f,  1.0f,  1.0f,								0.125f,	0.33f,//3
	1.0/1.6180339887f, 0.0f, 1.6180339887f,			0.0021f,0.002f,//4
	//2
	-1.0f, -1.0f, 1.0f,								0.253f,	0.002f,//5
	0.0f, -1.6180339887f, 1.0/1.6180339887f,		0.252f,	0.002f,//6
	1.0f, -1.0f,  1.0f,								0.5f,	0.002f,//7
	1.0/1.6180339887f, 0.0f, 1.6180339887f,			0.625f,	0.33f,//8
	-1.0/1.6180339887f, 0.0f, 1.6180339887f,		0.377f,	0.33f,//9
	//3
	1.0f,  1.0f,  1.0f,								0.541f,0.002f,//10
	0.0f, 1.6180339887f, 1.0 / 1.6180339887f,		0.54f,	0.002f,//11
	-1.0f,  1.0f, 1.0f,								0.75f,	0.002f,//12
	-1.0 / 1.6180339887f, 0.0f, 1.6180339887f,		0.875f,	0.33f,//13
	1.0 / 1.6180339887f, 0.0f, 1.6180339887f,		0.625f,	0.33f,//14
	//4
	-1.0f,  1.0f, 1.0f,								0.77f,	0.002f,//15
	-1.6180339887, 1.0 / 1.6180339887f,  0.0f,		1.0f,	0.002f,//16
	-1.6180339887, -1.0 / 1.6180339887f,  0.0f,		1.0f,	0.3f,//17
	-1.0f,  -1.0f, 1.0f,							0.875f,	0.3f,//18
	-1.0 / 1.6180339887f, 0.0f, 1.6180339887f,		0.771f,	0.002f,//19
	//5
	0.0f, 1.6180339887f, 1.0 / 1.6180339887f,		0.035f,0.333f,//20
	0.0f, 1.6180339887f, -1.0 / 1.6180339887f,		0.005f,	0.34f,//21
	-1.0f, 1.0f,  -1.0f,							0.25f,	0.34f,//22
	-1.6180339887, 1.0 / 1.6180339887f,  0.0f,		0.36f,	0.66f,//23
	-1.0f,  1.0f, 1.0f,								0.125f,	0.66f,//24
	//6
	1.6180339887, 1.0 / 1.6180339887f,  0.0f,		0.2541f,	0.333f,//25
	1.0f, 1.0f, -1.0f,								0.254f,	0.34f,//26
	0.0f, 1.6180339887f, -1.0 / 1.6180339887f,		0.501f,	0.34f,//27
	0.0f, 1.6180339887f, 1.0 / 1.6180339887f,		0.6f,	0.66f,//28
	1.0f,  1.0f,  1.0f,								0.375f,	0.66f,//29
	//7
	-1.6180339887, -1.0 / 1.6180339887f,  0.0f,		0.625f,	0.66f,//30
	-1.0f, -1.0f, -1.0f,							0.5051f,	0.333f,//31
	0.0f, -1.6180339887f, -1.0 / 1.6180339887f,		0.505f,	0.34f,//32
	0.0f, -1.6180339887f, 1.0 / 1.6180339887f,		0.75f,	0.34f,//33
	-1.0f,  -1.0f, 1.0f,							0.87f,	0.66f,//34
	//8
	0.0f, -1.6180339887f, 1.0 / 1.6180339887f,		0.7591f,0.333f,//35
	0.0f, -1.6180339887f, -1.0 / 1.6180339887f,		0.759f,	0.34f,//36
	1.0f, -1.0f, -1.0f,								1.0f,	0.34f,//37
	1.6180339887, -1.0 / 1.6180339887f,  0.0f,		1.0f,	0.66f,//38
	1.0f, -1.0f,  1.0f,								0.879f,	0.66f,//39
	//9
	1.6180339887, -1.0 / 1.6180339887f,  0.0f,		0.01f,	0.67f,//40
	1.0f, -1.0f, -1.0f,								0.23f,	0.67f,//41
	1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		0.30f,	1.0f,//42
	1.0f, 1.0f, -1.0f,								0.123f,	1.0f,//43
	1.6180339887, 1.0 / 1.6180339887f,  0.0f,		0.011f,0.67f,//44
	//10
	-1.0f, 1.0f,  -1.0f,							0.251f,	0.671f,//45
	-1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		0.25f,	0.67f,//46
	-1.0f, -1.0f, -1.0f,							0.49f,	0.67f,//47
	-1.6180339887, -1.0 / 1.6180339887f,  0.0f,		0.6f,	1.0f,//48
	-1.6180339887, 1.0 / 1.6180339887f,  0.0f,		0.38f,	1.0f,//49
	//11
	-1.0f, 1.0f,  -1.0f,							0.82f,	1.0f,//50
	-1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		0.74f,	0.67f,//51
	1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		0.5f,	0.67f,//52
	1.0f, 1.0f, -1.0f,								0.501f,0.671f,//53
	0.0f, 1.6180339887f, -1.0 / 1.6180339887f,		0.64f,	1.0f,//54
	//12
	-1.0f, -1.0f, -1.0f,							0.7591f,0.671f,//55
	-1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		0.759f,	0.67f,//56
	1.0 / 1.6180339887f, 0.0f, -1.6180339887f,		1.0f,	0.67f,//57
	1.0f, -1.0f, -1.0f,								1.0f,	1.0f,//58
	0.0f, -1.6180339887f, -1.0 / 1.6180339887f,		0.879f,	1.0f,//59
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,600, 600);
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
	CrearCubo();
	CreateShaders();
	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_ladrillos = Texture("Textures/ladrillos.tga");
	T_ladrillos.LoadTexture();
	T_asfalto = Texture("Textures/dirt.png");
	T_asfalto.LoadTexture();
	T_dado = Texture("Textures/p6.tga");
	T_dado.LoadTexture();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		//ejercicio 1:
		glm::mat4 model(1.0); 

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T_ladrillos.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_dado.UseTexture();
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}