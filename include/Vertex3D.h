#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../include/OBJLoader.h"

namespace Johnny
{
	class Vertex3D
	{
	public:
		Vertex3D();
		~Vertex3D();

		static const int SIZE;
		static void setVertexAttribPointer();

		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
	};
}

#endif

