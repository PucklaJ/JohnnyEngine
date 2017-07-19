#include "../include/Mesh3D.h"
#include <GL/glew.h>
#include "../include/Vertex3D.h"
#include "../include/LogManager.h"
#include <iostream>
#include "../include/ResourceManager.h"
#include <assimp/scene.h>


namespace Johnny
{
	Mesh3D::Mesh3D()
	{
		glGenBuffers(1, &m_vbo);
		if (m_vbo == 0)
		{
			Johnny::LogManager::error("Couldn't create VertexBuffer for Mesh", true, true, false);
		}
		else
		{
			glGenBuffers(1, &m_ibo);
			if (m_ibo == 0)
			{
				Johnny::LogManager::error("Couldn't create IndexBuffer for Mesh", true, true, false);
			}
			else
			{
				glGenVertexArrays(1, &m_vao);
				if (m_vao == 0)
				{
					Johnny::LogManager::error("Couldn't create VertexArrays for Mesh", true, true, false);
				}
			}
		}

		m_material.name = "NONE";

	}

	Mesh3D::Mesh3D(aiMesh* mesh, const aiScene* scene, bool switchZandY) : Mesh3D()
	{

		if (mesh->mMaterialIndex >= 0)
		{
			m_material = Material(scene->mMaterials[mesh->mMaterialIndex]);
			if (m_material.name == "NONE")
				m_material.name = "Material";
		}

		m_name = mesh->mName.C_Str();
		if (m_name == "")
			m_name = "NONE";

		std::vector<Vertex3D> vertices;
		std::vector<GLuint> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex3D vert;

			if (mesh->HasPositions())
			{
				vert.pos.x = mesh->mVertices[i].x;
				if (switchZandY)
				{
					vert.pos.y = mesh->mVertices[i].z;
					vert.pos.z = -mesh->mVertices[i].y;
				}
				else
				{
					vert.pos.y = mesh->mVertices[i].y;
					vert.pos.z = mesh->mVertices[i].z;
				}
			}


			if (mesh->HasTextureCoords(0))
			{
				if (mesh->mTextureCoords && mesh->mTextureCoords[0])
				{
					vert.uv.x = mesh->mTextureCoords[0][i].x;
					vert.uv.y = mesh->mTextureCoords[0][i].y;
				}
				else
				{
					vert.uv.x = vert.uv.y = 0.0f;
				}
			}

			if (mesh->HasNormals())
			{
				vert.normal.x = mesh->mNormals[i].x;
				if (switchZandY)
				{
					vert.normal.y = mesh->mNormals[i].z;
					vert.normal.z = -mesh->mNormals[i].y;
				}
				else
				{
					vert.normal.y = mesh->mNormals[i].y;
					vert.normal.z = mesh->mNormals[i].z;
				}
			}

			vertices.push_back(vert);
		}

		aiFace face;

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		Vertex3D* verticesArray = new Vertex3D[vertices.size()];
		GLuint* indicesArray = new GLuint[indices.size()];

		for (size_t i = 0; i < vertices.size(); i++)
		{
			verticesArray[i] = vertices[i];
		}

		for (size_t i = 0; i < indices.size(); i++)
		{
			indicesArray[i] = indices[i];
		}

		addVertices(verticesArray, vertices.size(), indicesArray, indices.size());

		delete[] verticesArray;
		delete[] indicesArray;
	}


	Mesh3D::~Mesh3D()
	{
		if (m_vbo != 0)
		{
			glDeleteBuffers(1, &m_vbo);
		}

		if (m_ibo != 0)
		{
			glDeleteBuffers(1, &m_ibo);
		}

		if (m_vao != 0)
		{
			glDeleteVertexArrays(1, &m_vao);
		}
	}

	void Mesh3D::addVertices(Vertex3D* vertices, unsigned int size, GLuint* indices, unsigned int indexSize)
	{
		if (m_vbo == 0 || m_ibo == 0 || m_vao == 0)
		{
			Johnny::LogManager::error("Couldn't add Vertices, because the Buffers aren't initialized");
			return;
		}


		m_vertexSize = size * Vertex3D::SIZE;
		m_indexSize = indexSize;

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertexSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(m_vao);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		Vertex3D::setVertexAttribPointer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glBindVertexArray(0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh3D::setMaterial(const Material& mat)
	{
		m_material = mat;
	}

	void Mesh3D::loadMaterial(Johnny::ResourceManager* res)
	{
		m_material.loadTextures(res);
	}

	void Mesh3D::render(Shader* s)
	{
		if (m_vbo != 0 && m_ibo != 0 && m_vao != 0)
		{
			glBindVertexArray(m_vao);

			if (s)
			{
				m_material.bind(s);
				glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
				m_material.unbind();
			}
			else
			{
				glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
			}


			glBindVertexArray(0);
		}

	}

}