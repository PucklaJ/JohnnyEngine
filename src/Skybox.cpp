#include "../include/Skybox.h"
#include "../include/Shader.h"
#include "../include/CubeMap3D.h"
#include "../include/MainClass.h"
#include "../include/ResourceManager.h"
#include "../include/Camera3D.h"
#include "../include/LogManager.h"
#include "../include/RenderManager.h"
#include "../include/Matrix4.h"
#include <iostream>

namespace Johnny
{
	Shader* Skybox::SKYBOX_SHADER = nullptr;
	SkyboxMesh* Skybox::SKYBOX_MESH = nullptr;



	void Skybox::clear()
	{
		if (SKYBOX_MESH)
		{
			delete SKYBOX_MESH;
			SKYBOX_MESH = nullptr;
		}

		if (SKYBOX_SHADER)
		{
			delete SKYBOX_SHADER;
			SKYBOX_SHADER = nullptr;
		}

	}

	Skybox::Skybox() : Actor("Skybox")
	{
		m_castsShadows = false;
	}


	Skybox::~Skybox()
	{
	}

	bool Skybox::init()
	{
		m_cubeMap = new CubeMap3D(m_textures[SkyboxTex::TOP], m_textures[SkyboxTex::BOTTOM], m_textures[SkyboxTex::LEFT], m_textures[SkyboxTex::RIGHT], m_textures[SkyboxTex::FRONT], m_textures[SkyboxTex::BACK], m_mainClass->getResourceManager());

		if (SKYBOX_SHADER == nullptr)
		{
			SKYBOX_SHADER = new Shader();
			SKYBOX_SHADER->setLoadDefaultUniforms(false);
			SKYBOX_SHADER->addVertexShader(m_mainClass->getResourceManager()->loadShader("vertexShaderSkybox.glsl"));
			SKYBOX_SHADER->addFragmentShader(m_mainClass->getResourceManager()->loadShader("fragmentShaderSkybox.glsl"));

			SKYBOX_SHADER->addAttribute("position", 0);

			SKYBOX_SHADER->link();

			SKYBOX_SHADER->addUniform("projectionMatrix");
			SKYBOX_SHADER->addUniform("cubeMap");

			m_mainClass->getRenderManager()->addShader(SKYBOX_SHADER);
		}

		if (SKYBOX_MESH == nullptr)
		{
#define SIZE 500.0f

			SkyboxVertex vertices[36];

			// FRONT
			vertices[0].position = glm::vec3(-SIZE, SIZE, -SIZE);
			vertices[1].position = glm::vec3(-SIZE, -SIZE, -SIZE);
			vertices[2].position = glm::vec3(SIZE, -SIZE, -SIZE);
			vertices[3].position = glm::vec3(SIZE, -SIZE, -SIZE);
			vertices[4].position = glm::vec3(SIZE, SIZE, -SIZE);
			vertices[5].position = glm::vec3(-SIZE, SIZE, -SIZE);

			// LEFT
			vertices[6].position = glm::vec3(-SIZE, -SIZE, SIZE);
			vertices[7].position = glm::vec3(-SIZE, -SIZE, -SIZE);
			vertices[8].position = glm::vec3(-SIZE, SIZE, -SIZE);
			vertices[9].position = glm::vec3(-SIZE, SIZE, -SIZE);
			vertices[10].position = glm::vec3(-SIZE, SIZE, SIZE);
			vertices[11].position = glm::vec3(-SIZE, -SIZE, SIZE);

			// RIGHT
			vertices[12].position = glm::vec3(SIZE, -SIZE, -SIZE);
			vertices[13].position = glm::vec3(SIZE, -SIZE, SIZE);
			vertices[14].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[15].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[16].position = glm::vec3(SIZE, SIZE, -SIZE);
			vertices[17].position = glm::vec3(SIZE, -SIZE, -SIZE);

			// BACK
			vertices[18].position = glm::vec3(-SIZE, -SIZE, SIZE);
			vertices[19].position = glm::vec3(-SIZE, SIZE, SIZE);
			vertices[20].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[21].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[22].position = glm::vec3(SIZE, -SIZE, SIZE);
			vertices[23].position = glm::vec3(-SIZE, -SIZE, SIZE);

			// TOP
			vertices[24].position = glm::vec3(-SIZE, SIZE, -SIZE);
			vertices[25].position = glm::vec3(SIZE, SIZE, -SIZE);
			vertices[26].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[27].position = glm::vec3(SIZE, SIZE, SIZE);
			vertices[28].position = glm::vec3(-SIZE, SIZE, SIZE);
			vertices[29].position = glm::vec3(-SIZE, SIZE, -SIZE);

			// BOTTOM
			vertices[30].position = glm::vec3(-SIZE, -SIZE, -SIZE);
			vertices[31].position = glm::vec3(-SIZE, -SIZE, SIZE);
			vertices[32].position = glm::vec3(SIZE, -SIZE, -SIZE);
			vertices[33].position = glm::vec3(SIZE, -SIZE, -SIZE);
			vertices[34].position = glm::vec3(-SIZE, -SIZE, SIZE);
			vertices[35].position = glm::vec3(SIZE, -SIZE, SIZE);

			SKYBOX_MESH = new SkyboxMesh();
			SKYBOX_MESH->addVertices(vertices, 36);
		}

		setShader(SKYBOX_SHADER);

		return true;
	}

	bool Skybox::update()
	{
		return true;
	}

	bool Skybox::render()
	{
		glm::mat4 projectionMatrix = m_mainClass->getCamera3D()->getViewMatrix();
		projectionMatrix[3][0] = 0;
		projectionMatrix[3][1] = 0;
		projectionMatrix[3][2] = 0;
		projectionMatrix = Transform3D::getProjectionMatrix() * projectionMatrix;

		SKYBOX_SHADER->setUniformMat4("projectionMatrix", projectionMatrix);
		m_cubeMap->bind(SKYBOX_SHADER, "cubeMap", 0, GL_TEXTURE_CUBE_MAP);
		SKYBOX_MESH->render();
		m_cubeMap->unbind(0, GL_TEXTURE_CUBE_MAP);

		return true;
	}

	void Skybox::quit()
	{
		delete m_cubeMap;
	}

	void Skybox::setTexture(short which, const std::string& fileName)
	{
		m_textures[which] = fileName;
	}

	SkyboxMesh::SkyboxMesh()
	{
		glGenBuffers(1, &m_vbo);
		if (m_vbo == 0)
		{
			LogManager::error("Couldn't generate Vertex Buffer for SkyboxMesh", true, true, false);
		}
		else
		{
			glGenVertexArrays(1, &m_vao);
			if (m_vao == 0)
			{
				LogManager::error("Couldn't generate VertexArray for SkyboxMesh", true, true, false);
			}
		}

	}

	SkyboxMesh::~SkyboxMesh()
	{
		if (m_vbo != 0)
			glDeleteBuffers(1, &m_vbo);
		if (m_vao != 0)
			glDeleteVertexArrays(1, &m_vao);
	}

	void SkyboxMesh::addVertices(SkyboxVertex* vertices, unsigned int numVertices)
	{
		if (m_vbo == 0 || m_vao == 0)
		{
			LogManager::error("Couldn't add Vertices, because the Buffers aren't initialized");
			return;
		}

		m_numVertices = numVertices;

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(SkyboxVertex), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(m_vao);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SkyboxVertex), (GLvoid*)offsetof(SkyboxVertex, position));

		glBindVertexArray(0);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SkyboxMesh::render()
	{
		if (m_vbo != 0 && m_vao != 0)
		{
			glBindVertexArray(m_vao);

			glDrawArrays(GL_TRIANGLES, 0, m_numVertices);

			glBindVertexArray(0);
		}
	}
}
