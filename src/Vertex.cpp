#include "Vertex.h"
#include <cstdlib>

Vertex::Vertex() :
	pos(0.0, 0.0, 0.0),
	normal(0.0,0.0,0.0),
	uv(1.0,1.0)
{

}

Vertex::~Vertex()
{
}

void Vertex::setVertexAttribPointer()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), (GLuint*)offsetof(Vertex, uv));

}

const int Vertex::SIZE = 8;
