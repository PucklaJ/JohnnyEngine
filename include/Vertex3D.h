#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../include/OBJLoader.h"

namespace Johnny
{	
	/*! \brief A class which stores Vertex data for a 3D mesh
	 *
	 */
	class Vertex3D
	{
	public:
		Vertex3D();
		~Vertex3D();

		static const int SIZE; 				  //!< The size of the Vertex in bytes
		static void setVertexAttribPointer(); //!< Sets the vertex attributes for a Shader

		glm::vec3 pos;						  //!< The position of the Vertex3D
		glm::vec3 normal;					  //!< The normal of the Vertex3D
		glm::vec2 uv;						  //!< The uv coordinates / texture coordinates of the Vertex3D
	};
}

#endif

