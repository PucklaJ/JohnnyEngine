#pragma once
#include <GL/glew.h>
#include "../include/OBJLoader.h"
#include <assimp/scene.h>



namespace Johnny
{
	class ResourceManager;
	class Vertex3D;
	class Shader;

	class Mesh3D
	{
	public:
		Mesh3D();
		Mesh3D(aiMesh*, const aiScene*, bool);
		~Mesh3D();

		void addVertices(Vertex3D*, unsigned int, GLuint*, unsigned int);
		void setMaterial(const Material&);
		void loadMaterial(ResourceManager*);
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
}

