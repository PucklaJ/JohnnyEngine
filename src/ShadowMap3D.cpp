#include "../include/ShadowMap3D.h"
#include "../include/FrameBuffer.h"
#include "../include/Shader.h"
#include "../include/Transform3D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../include/mathematics.h"
#include "../include/MainClass.h"
#include <iostream>
#include "../include/Light3D.h"
#include "../include/RenderManager.h"
#include "../include/Entity3D.h"
#include "../include/Model3D.h"
#include "../include/Colors.h"


namespace Johnny
{
    void ShadowMap3DShaderUpdater::setUniforms(Transform3D* m,const unsigned int index)
    {
        if(index == ShaderUpdater::TRANSFORM_WORLD)
        {
            m_shader->setUniform("worldMatrix",m->getTransformation());
        }
    }
    
    void ShadowMap3DShaderUpdater::setUniforms(Entity3D* m,const unsigned int index)
    {
        m->getModel()->render(m_shader);
    }
    
	ShadowMap3D::ShadowMap3D(GLsizei width, GLsizei height) : Texture(nullptr, width, height,GL_LINEAR, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT),
        m_lightSpaceMatrix(1)
	{
        m_width = width;
        m_height = height;
        
        Colorf borderColor = Colors::WHITE;
        glTextureParameteri(m_texture,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
        glTextureParameteri(m_texture,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
        glTextureParameterfv(m_texture,GL_TEXTURE_BORDER_COLOR,&borderColor.r);
        
		m_frameBuffer = new FrameBuffer();
		m_frameBuffer->bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, getBuffer(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		m_frameBuffer->unbind();
	}


	ShadowMap3D::~ShadowMap3D()
	{
		delete m_frameBuffer;
	}

	void ShadowMap3D::render(MainClass* m, Shader* s)
	{
		if (m_curLight == 0)
			return;

		glViewport(0, 0, m_width, m_height);

		m_frameBuffer->bind();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		configureMatricesAndShader(s);
		GLint params[4];
		glGetIntegerv(GL_VIEWPORT, params);
        glDepthRange(-2.0f,2.0f);
        glEnable(GL_DEPTH_CLAMP);
		m->getRenderManager()->renderSceneForShadowMap(s);
        glDepthRange(0.0f,1.0f);
        glDisable(GL_DEPTH_CLAMP);
		glGetIntegerv(GL_VIEWPORT, params);
		m->getBackBuffer()->bind();

		glViewport(0, 0, (GLsizei)m->getNativeRes().x, (GLsizei)m->getNativeRes().y);
	}

	void ShadowMap3D::setPointLight(PointLight3D* light)
	{
		m_pointLight = light;
		m_curLight = SHADOW_POINT;
	}

	void ShadowMap3D::setDirectionalLight(DirectionalLight3D* light)
	{
		m_directionalLight = light;
		m_curLight = SHADOW_DIR;
	}

	void ShadowMap3D::setSpotLight(SpotLight3D* light)
	{
		m_spotLight = light;
		m_curLight = SHADOW_SPOT;
	}

	void ShadowMap3D::loadMatrix(Shader* s, const std::string& name)
	{
		s->setUniform(name, m_lightSpaceMatrix);
	}

	void ShadowMap3D::load(Shader* s, GLuint index, const std::string & matrixName, const std::string & textureName)
	{
		s->setUniform(matrixName, m_lightSpaceMatrix);
		bind(s, textureName, index);
	}

	void ShadowMap3D::configureMatricesAndShader(Shader* s)
	{
		Matrix4f lightProjection(1);
		Matrix4f lightView(1);
		Vector3f direction;
		Vector3f position;

		if (m_curLight == SHADOW_DIR)
		{
			direction = m_directionalLight->direction;

			lightView = Matrix4f::lookAt(-direction * 1.3f, -direction * 1.3f + direction, Vector3f(0.0f, 1.0f, 0.0f));
            // T left,T right,T bottom,T top,T zNear,T zFar);
			//lightProjection = toMy<GLfloat>(glm::ortho(-(GLfloat)m_width/2.0f, (GLfloat)m_width/2.0f, -(GLfloat)m_height/2.0f, (GLfloat)m_height/2.0f, 0.1f, 100.0f));
			lightProjection = toMy<GLfloat>(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f));
        }
		else if (m_curLight == SHADOW_SPOT)
		{
			direction = m_spotLight->direction;
			position = m_spotLight->position;

			lightView = Matrix4f::lookAt(position, position + direction, Vector3f(0.0f, 1.0f, 0.0f));
			lightProjection = Matrix4f::perspective(/*m_spotLight->outerCutOff * (float)M_PI / 180.0f*/70.0f,
                                                    (float)m_width / (float)m_height/*MainClass::getInstance()->getNativeRes().x / MainClass::getInstance()->getNativeRes().y*/,
                                                    clamp(1000.0f, 100.0f, 1000.0f),
                                                    clamp(0.1f, 1.0f, 10.0f));
		}

		m_lightSpaceMatrix = lightProjection * lightView;

		s->bind();
		loadMatrix(s);
	}

}
