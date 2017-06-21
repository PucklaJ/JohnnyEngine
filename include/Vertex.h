#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "OBJLoader.h"

class Vertex
{
public:
	Vertex();
	~Vertex();

	static const int SIZE;
	static void setVertexAttribPointer();

	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;
};

#endif

