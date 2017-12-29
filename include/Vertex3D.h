#ifndef VERTEX_H
#define VERTEX_H
#include <GL/glew.h>
#include "OBJLoader.h"
#include "Vector3.h"
#include "Vector2.h"

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

		Vector3f pos;						  //!< The position of the Vertex3D
		Vector3f normal;					  //!< The normal of the Vertex3D
		Vector2f uv;						  //!< The uv coordinates / texture coordinates of the Vertex3D
	};
}

#endif

