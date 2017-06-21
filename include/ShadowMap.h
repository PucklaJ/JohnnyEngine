#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
#include <string>

#define SHADOW_POINT 1
#define SHADOW_DIR 2
#define SHADOW_SPOT 3

class FrameBuffer;
class PointLight;
class DirectionalLight;
class SpotLight;
class Shader;

namespace SDL
{
	class MainClass;
}

class ShadowMap : public Texture
{
public:
	ShadowMap(GLsizei,GLsizei);
	~ShadowMap();

	void render(SDL::MainClass*,Shader*);

	void setPointLight(PointLight*);
	void setDirectionalLight(DirectionalLight*);
	void setSpotLight(SpotLight*);
	void loadMatrix(Shader*,const std::string& name = "lightSpaceMatrix");
	void load(Shader*,GLuint index = 0,const std::string& matrixName = "lightSpaceMatrix",const std::string& textureName = "shadowMap");

	FrameBuffer* getFrameBuffer() { return m_frameBuffer; }
private:
	void configureMatricesAndShader(Shader*);

	GLsizei m_width;
	GLsizei m_height;
	FrameBuffer* m_frameBuffer = nullptr;
	PointLight* m_pointLight = nullptr;
	DirectionalLight* m_directionalLight = nullptr;
	SpotLight* m_spotLight = nullptr;
	GLuint m_curLight = 0;

	glm::mat4 m_lightSpaceMatrix;
};

