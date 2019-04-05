#pragma once

#include <glew.h>
#include <glm.hpp>
/* Esta clase base coloquialmente llamada superclase) se requiere heredar en DirectionalLight, PointLight  y SpotLight
Esto es porque las 3 Fuentes de iluminación comparten las variables color, ambientIntensity y diffuseIntensity
*/
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

