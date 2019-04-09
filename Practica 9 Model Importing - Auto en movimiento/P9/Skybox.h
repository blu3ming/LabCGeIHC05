/*
Facultad de Ingeniería - UNAM
2019 - Creado por Josué Cruz Mier
*/
#pragma once

#include <vector>
#include <string>

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "CommonValues.h"
#include "Mesh_texturizado.h"
#include "Shader_light.h"

class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations);
	void bindCubeMapTexture();
	void unbinedCubeMapTexture();
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	Mesh* skyMesh;
	Shader* skyShader;
	
	GLuint textureId;
	GLuint uniformProjection, uniformView;
};

