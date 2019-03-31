/*
* definition.h
*Basado en el código creado por
*  Created on: 06/09/2016
*      Author: reynaldo Martell
*/

#ifndef HEADERS_DEFINITION_H_
#define HEADERS_DEFINITION_H_

#include <glm.hpp>
#include <glew.h>
#include <gtc/random.hpp>
#include <iostream>

typedef struct _VertexColor {

	_VertexColor() {
	}

	_VertexColor(glm::vec3 position, glm::vec3 color) {
		this->position = position;
		this->color = color;
	}

	glm::vec3 position;
	glm::vec3 color;
} VertexColor;

#endif /* HEADERS_DEFINITION_H_ */
