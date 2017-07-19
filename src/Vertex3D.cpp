#include "../include/Vertex3D.h"
#include <cstdlib>

namespace Johnny
{
	Vertex3D::Vertex3D() :
		pos(0.0, 0.0, 0.0),
		normal(0.0, 0.0, 0.0),
		uv(1.0, 1.0)
	{

	}

	Vertex3D::~Vertex3D()
	{
	}

	void Vertex3D::setVertexAttribPointer()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex3D::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex3D, pos));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex3D::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex3D, normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertex3D::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex3D, uv));

	}

	const int Vertex3D::SIZE = 8;
}
