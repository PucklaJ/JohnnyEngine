#pragma once
#include <GL/glew.h>
#include "OBJLoader.h"
#include <assimp/scene.h>

class Vertex;
class Shader;

namespace SDL
{
	class ResourceManager;
}

class Mesh
{
public:
	Mesh();
	Mesh(aiMesh*,const aiScene*,bool);
	~Mesh();

	void addVertices(Vertex*, unsigned int,GLuint*,unsigned int);
	void setMaterial(const Material&);
	void loadMaterial(SDL::ResourceManager*);
	void render(Shader* s = nullptr);

	const std::string& getName() const { return m_name; }
	const Material& getMaterial() const { return m_material; }
private:
	GLuint m_vbo = 0;
	GLuint m_ibo = 0;
	GLuint m_vao = 0;
	unsigned int m_vertexSize = 0;
	unsigned int m_indexSize = 0;
	Material m_material;
	std::string m_name = "NONE";
};

