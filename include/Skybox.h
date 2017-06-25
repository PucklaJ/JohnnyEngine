#pragma once
#include "Actor.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

class CubeMap;
class Shader;

class SkyboxVertex
{
public:
	glm::vec3 position;
};

class SkyboxMesh
{
public:
	SkyboxMesh();
	~SkyboxMesh();

	void addVertices(SkyboxVertex*,unsigned int);

	void render();
private:
	GLuint m_vbo = 0;
	GLuint m_vao = 0;

	GLsizei m_numVertices = 0;
};

enum SkyboxTex
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	FRONT,
	BACK
};

class Skybox : public SDL::Actor
{
public:
	static void clear();

	Skybox();
	~Skybox();

	bool init() override;
	bool update() override;
	bool render() override;
	void quit() override;

	void setTexture(short, const std::string&);

private:
	static Shader* SKYBOX_SHADER;
	static SkyboxMesh* SKYBOX_MESH;

	CubeMap* m_cubeMap = nullptr;
	std::string m_textures[6];
	bool m_texturesSet = false;
};

