/*
Semestre 2019-2
Práctica 9: Animación y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh_texturizado.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

#include"Model.h"
#include"Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

float x,y,z, giro1=0.0;
int a = 0, giro = 0, fin = 0, vuelta_1 = 0, vuelta_2 = 0, vuelta_3 = 0, vuelta_4 = 0;
int giro_r1 = 0, encendido = 0;
int subida = 0, arriba = 0, bajada = 0;
int derecha = 0, abajo = 0, abajo1 = 0, izquierda = 0;
int noventa = 90;
float verde=1.0f, rojo=0.0f;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture dadoTexture;
//materiales
Material Material_brillante;
Material Material_opaco;
//luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model X_Wing;
Model Roads;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Skybox skybox;

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";
//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);
		
		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects() 
{
	unsigned int indices[] = {		
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//	x      y      z			u	  v			nx	  ny    nz
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-15.0f, 0.0f, -15.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		15.0f, 0.0f, -15.0f,	15.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-15.0f, 0.0f, 15.0f,	0.0f, 15.0f,	0.0f, -1.0f, 0.0f,
		15.0f, 0.0f, 15.0f,		15.0f, 15.0f,	0.0f, -1.0f, 0.0f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);
}

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.48f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.48f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.52f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.73f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.73f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.52f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.77f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.98f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.98f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.77f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.23f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.23f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.27f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.48f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.48f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.27f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};
	
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
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
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCubo();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/Grass3.png");
	plainTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado.tga");
	dadoTexture.LoadTextureA();
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);
	
	Roads = Model();
	Roads.LoadModel("Models/Roads.obj");
	X_Wing = Model();
	X_Wing.LoadModel("Models/x-wing.obj");
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt.3ds");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");
	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.3f, 0.3f,
								0.0f, 0.0f, -1.0f);
//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(verde, rojo, 0.0f,
								0.0f, 1.0f,
								-2.0f, -0.5f,-1.4f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//Carga imagenes del skybox
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/hills_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/hills_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/hills_up.tga");
	skyboxFaces.push_back("Textures/Skybox/hills_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/hills_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/hills_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//importer de ASSIMP para probar que funciona
//	Assimp::Importer importer = Assimp::Importer();

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		pointLights[0] = PointLight(rojo, verde, 0.0f,
			0.0f, 1.0f,
			-2.0f, -0.5f, -1.4f,
			0.3f, 0.2f, 0.1f);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; 
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//muestra el skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0);
		/*
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();
		*/
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		plainTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		////model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//dadoTexture.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[3]->RenderMesh();
		
		//entorno 3d
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Roads.RenderModel();

		//coche
		model = glm::mat4(1.0);
		glm::mat4 modeltemp(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -3.2f));
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::rotate(model, -giro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giro1 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modeltemp = model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Kitt_M.RenderModel();

		//model = glm::mat4(1.0);
		model = glm::translate(modeltemp, glm::vec3(-0.58f, -1.2f, -0.08f));
		//model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giro_r1 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));;
		model = glm::rotate(model, a * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();
		
		//model = glm::mat4(1.0);
		model = glm::translate(modeltemp, glm::vec3(0.58f, -1.2f, -0.08f));
		//model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -giro_r1 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -a * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();
		
		//model = glm::mat4(1.0);
		model = glm::translate(modeltemp, glm::vec3(0.55f, 1.4f, -0.15f));
		//model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -a * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();
		
		//model = glm::mat4(1.0);
		model = glm::translate(modeltemp, glm::vec3(-0.55f, 1.4f, -0.15f));
		//model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, a * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();
		/*
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, -90* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Blackhawk_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.53f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Camino_M.RenderModel();
		*/
			glUseProgram(0);

		mainWindow.swapBuffers();
		//avanza arriba y fin
		if (fin == 0) {
			vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			x += 0.02;
			a += 5;
			giro_r1 -= 5;
			if (giro_r1 < 0) { giro_r1 = 0; }
			if (x > 5.0) { fin == 1; vuelta_1 = 1; }
		}
		
		//primera vuelta
		if (vuelta_1 == 1) {
			fin = 1; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro += 1;
			z += 0.02;
			x += 0.02;
			giro_r1 += 2;
			if (giro_r1 > 45) { giro_r1 =45; }
			if (giro == noventa) { derecha = 1; vuelta_1 = 0; noventa += 90; }
		}

		//avanza derecha y fin
		if (derecha == 1) {
			fin = 1; vuelta_1 = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			z += 0.02;
			giro_r1 -= 5;
			if (giro_r1 < 0) { giro_r1 = 0; }
			if (z > 5.0) { vuelta_2 = 1; derecha = 0;}
		}

		//segunda vuelta
		if (vuelta_2 == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro += 1;
			x -= 0.02;
			z += 0.02;
			giro_r1 += 2;
			if (giro_r1 > 45) { giro_r1 = 45; }
			if (giro== noventa) { abajo = 1; vuelta_2 = 0; noventa += 90;}
		}

		//avanza antes de subida
		if (abajo == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			x -= 0.02;
			giro_r1 -= 5;
			if (giro_r1 < 0) { giro_r1 = 0; }
			if (x<4.8) { subida = 1; abajo = 0; }
		}
		
		//subida
		if (subida == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro1 += 0.13;
			x -= 0.03;
			if (x < 3.5) { y += 0.007; }
			else { y += 0; }
			rojo = 1.0f;
			verde = 0.8f;
			if (giro1 > 16.0)giro1 = 16.0;
			if (x < 0.5) { arriba = 1; subida = 0; }
		}

		//arriba
		if (arriba == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro1 -= 0.3;
			x -= 0.03;
			y += 0.005;
			if (y > 0.8) y = 0.8;
			verde = 0.0f;
			rojo = 1.0f;
			if (giro1 < 0.0) giro1 = 0.0;
			if (x < -3.0) { bajada = 1; arriba = 0; }
		}

		//bajada
		if (bajada == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro1 -= 0.22;
			x -= 0.03;
			y -= 0.006;
			if (giro1 < -16.0)giro1 = -16.0;
			if (y < 0.0) y = 0.0;
			if (x < -6.6) { abajo1 = 1; bajada = 0; }
		}

		//abajo1
		if (abajo1 == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			vuelta_3 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro1 += 0.33;
			x -= 0.03;
			y -= 0.006;
			if (giro1 > 0.0) giro1 = 0.0;
			if (y < 0.0) y = 0.0;
			if (x < -8.5) { vuelta_3 = 1; abajo1 = 0; }
		}

		//tercera vuelta
		if (vuelta_3 == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; izquierda = 0; vuelta_4 = 0;
			a += 5;
			giro += 1;
			x -= 0.02;
			z -= 0.02;
			giro_r1 += 2;
			if (giro_r1 > 45) { giro_r1 = 45; }
			if (giro == noventa) { izquierda = 1; vuelta_3 = 0; noventa += 90;}
		}

		//izquierda
		if (izquierda == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; vuelta_4 = 0;
			a += 5;
			z -= 0.02;
			verde = 1.0f;
			rojo = 0.0f;
			giro_r1 -= 5;
			if (giro_r1 < 0) { giro_r1 = 0; }
			if (z<1.8) { vuelta_4 = 1; izquierda = 0; }
		}
		
		//cuarta vuelta
		if (vuelta_4 == 1) {
			fin = 1; vuelta_1 = 0; derecha = 0; vuelta_2 = 0; abajo = 0; subida = 0; arriba = 0; bajada = 0;
			abajo1 = 0; vuelta_3 = 0; izquierda = 0;
			a += 5;
			giro += 1;
			x += 0.02;
			z -= 0.02;
			giro_r1 += 2;
			if (giro_r1 > 45) { giro_r1 = 45; }
			if (giro == noventa) { fin = 0; vuelta_4 = 0; noventa += 90;}
		}
	}

	return 0;
}