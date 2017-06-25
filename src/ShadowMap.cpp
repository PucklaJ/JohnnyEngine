#include <ShadowMap.h>
#include <FrameBuffer.h>
#include <Shader.h>
#include <Transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mathematics.h>
#include <MainClass.h>
#include <iostream>
#include <Light.h>


ShadowMap::ShadowMap(GLsizei width, GLsizei height) : Texture(nullptr,width,height,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_FLOAT),
	m_width(width),
	m_height(height)
{
	m_frameBuffer = new FrameBuffer();
	m_frameBuffer->bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, getBuffer(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	m_frameBuffer->unbind();
}


ShadowMap::~ShadowMap()
{
	delete m_frameBuffer;
}

void ShadowMap::render(SDL::MainClass* m,Shader* s)
{
	if (m_curLight == 0)
		return;

	glViewport(0, 0, m_width, m_height);

	m_frameBuffer->bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	configureMatricesAndShader(s);
	//glCullFace(GL_FRONT);
	GLint params[4];
	glGetIntegerv(GL_VIEWPORT, params);
	m->renderSceneForShadowMap(s);
	glGetIntegerv(GL_VIEWPORT, params);
	//glCullFace(GL_BACK);
	m->getBackBuffer()->bind();

	glViewport(0, 0, (GLsizei)m->getNativeRes().x, (GLsizei)m->getNativeRes().y);
}

void ShadowMap::setPointLight(PointLight* light)
{
	m_pointLight = light;
	m_curLight = SHADOW_POINT;
}

void ShadowMap::setDirectionalLight(DirectionalLight* light)
{
	m_directionalLight = light;
	m_curLight = SHADOW_DIR;
}

void ShadowMap::setSpotLight(SpotLight* light)
{
	m_spotLight = light;
	m_curLight = SHADOW_SPOT;
}

void ShadowMap::loadMatrix(Shader* s,const std::string& name)
{
	s->setUniformMat4(name, m_lightSpaceMatrix);
}

void ShadowMap::load(Shader* s,GLuint index,const std::string & matrixName, const std::string & textureName)
{
	s->setUniformMat4(matrixName, m_lightSpaceMatrix);
	bind(s, textureName,index);
}

void ShadowMap::configureMatricesAndShader(Shader* s)
{
	glm::mat4 lightProjection;
	glm::mat4 lightView;

	if (m_curLight == SHADOW_DIR)
	{
		lightView = glm::lookAt(-m_directionalLight->direction*4.582f,-m_directionalLight->direction*4.582f+m_directionalLight->direction, glm::vec3(0.0, 1.0, 0.0));
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
	}
	else if (m_curLight == SHADOW_SPOT)
	{

		lightView = glm::lookAt(m_spotLight->position, m_spotLight->position + m_spotLight->direction, glm::vec3(0.0, 1.0, 0.0));
		lightProjection = glm::perspective(/*m_spotLight->outerCutOff * (float)MATH_PI / 180.0f*/Transform::getFOV() / 180.0f * (float)MATH_PI, /*(float)m_width / (float)m_height*/SDL::MainClass::getInstance()->getNativeRes().x/SDL::MainClass::getInstance()->getNativeRes().y, glm::clamp(Transform::getNearPlane(),1.0f,10.0f), glm::clamp(Transform::getFarPlane(),100.0f,1000.0f));
	}

	m_lightSpaceMatrix = lightProjection * lightView;

	s->bind();
	loadMatrix(s);
}
