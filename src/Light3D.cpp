#include "../include/Light3D.h"
#include "../include/Shader.h"
#include <sstream>
#include <iostream>
#include "../include/ShadowMap3D.h"
#include "../include/MainClass.h"

#define MATH_PI 3.14159265f

namespace Johnny
{
	glm::vec4 Lighting3D::ambientLight = glm::vec4(1.0, 1.0, 1.0, 1.0);

	void PointLight3D::load(Shader* s, PointLight3D* lights, unsigned int size, const std::string & name, GLuint shadowMapStartIndex)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			lights[i].load(s, i, true, name, shadowMapStartIndex++);
		}
	}

	PointLight3D::PointLight3D(const glm::vec3& _position, const glm::vec3& _diffuse, const glm::vec3& _specular, GLfloat _quadratic, GLfloat _linear, GLfloat _constant) :
		position(_position),
		diffuse(_diffuse),
		specular(_specular),
		quadratic(_quadratic),
		linear(_linear),
		constant(_constant)
	{
	}

	PointLight3D::~PointLight3D()
	{
		if (shadowMap)
			delete shadowMap;
	}

	void PointLight3D::load(Shader* s, GLuint index, bool isArray, const std::string& name, GLuint shadowMapIndex)
	{
		std::stringstream stream;
		std::string prefix;

		if (isArray)
			stream << name << "[" << index << "]" << ".";
		else
			stream << name << ".";

		stream >> prefix;

		s->setUniformVec3(prefix + "position", position);
		s->setUniformVec3(prefix + "diffuse", diffuse);
		s->setUniformVec3(prefix + "specular", specular);
		s->setUniformf(prefix + "quadratic", quadratic);
		s->setUniformf(prefix + "linear", linear);
		s->setUniformf(prefix + "constant", constant);
		s->setUniformi(prefix + "castsShadow", castsShadow);
		if (shadowMap)
			shadowMap->load(s, shadowMapIndex, prefix + "shadowMap.lightSpaceMatrix", prefix + "shadowMap.texture");
	}

	void PointLight3D::setShadowMap(GLsizei width, GLsizei height)
	{
		shadowMap = new ShadowMap3D(width, height);
		shadowMap->setPointLight(this);
		castsShadow = true;
	}

	void DirectionalLight3D::load(Shader* s, DirectionalLight3D* lights, unsigned int size, const std::string & name, GLuint shadowMapStartIndex)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			lights[i].load(s, i, true, name, shadowMapStartIndex++);
		}
	}

	DirectionalLight3D::DirectionalLight3D(const glm::vec3& _direction, const glm::vec3 & _diffuse, const glm::vec3 & _specular) :
		direction(_direction),
		diffuse(_diffuse),
		specular(_specular)
	{
	}

	DirectionalLight3D::~DirectionalLight3D()
	{
		if (shadowMap)
			delete shadowMap;
	}

	void DirectionalLight3D::load(Shader* s, GLuint index, bool isArray, const std::string & name, GLuint shadowMapIndex)
	{
		std::stringstream stream;
		std::string prefix;

		if (isArray)
			stream << name << "[" << index << "]" << ".";
		else
			stream << name << ".";

		stream >> prefix;

		s->setUniformVec3(prefix + "direction", direction);
		s->setUniformVec3(prefix + "diffuse", diffuse);
		s->setUniformVec3(prefix + "specular", specular);
		s->setUniformi(prefix + "castsShadow", castsShadow);
		if (shadowMap)
			shadowMap->load(s, shadowMapIndex, prefix + "shadowMap.lightSpaceMatrix", prefix + "shadowMap.texture");
	}

	void DirectionalLight3D::setShadowMap(GLsizei width, GLsizei height)
	{
		shadowMap = new ShadowMap3D(width, height);
		shadowMap->setDirectionalLight(this);
		castsShadow = true;
	}

	void SpotLight3D::load(Shader* s, SpotLight3D* lights, unsigned int size, const std::string & name, GLuint shadowMapStartIndex)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			lights[i].load(s, i, true, name, shadowMapStartIndex);
		}
	}

	SpotLight3D::SpotLight3D(const glm::vec3& _position, const glm::vec3& _direction, GLfloat _innerCutOff, GLfloat _outerCutOff, const glm::vec3 & _diffuse, const glm::vec3 & _specular, GLfloat _quadratic, GLfloat _linear, GLfloat _constant) :
		position(_position),
		diffuse(_diffuse),
		specular(_specular),
		innerCutOff(_innerCutOff),
		outerCutOff(_outerCutOff),
		quadratic(_quadratic),
		linear(_linear),
		constant(_constant)
	{
	}

	SpotLight3D::~SpotLight3D()
	{
		if (shadowMap)
			delete shadowMap;
	}

	void SpotLight3D::load(Shader* s, GLuint index, bool isArray, const std::string & name, GLuint shadowMapIndex)
	{
		std::stringstream stream;
		std::string prefix;

		if (isArray)
			stream << name << "[" << index << "]" << ".";
		else
			stream << name << ".";

		stream >> prefix;

		s->setUniformVec3(prefix + "position", position);
		s->setUniformVec3(prefix + "direction", direction);
		s->setUniformVec3(prefix + "diffuse", diffuse);
		s->setUniformVec3(prefix + "specular", specular);
		s->setUniformf(prefix + "innerCutOff", cos(innerCutOff / 180.0f * MATH_PI));
		s->setUniformf(prefix + "outerCutOff", cos(outerCutOff / 180.0f * MATH_PI));
		s->setUniformf(prefix + "quadratic", quadratic);
		s->setUniformf(prefix + "linear", linear);
		s->setUniformf(prefix + "constant", constant);
		s->setUniformi(prefix + "castsShadow", castsShadow);
		if (shadowMap)
			shadowMap->load(s, shadowMapIndex, prefix + "shadowMap.lightSpaceMatrix", prefix + "shadowMap.texture");
	}

	void SpotLight3D::setShadowMap(GLsizei width, GLsizei height)
	{
		shadowMap = new ShadowMap3D(width, height);
		shadowMap->setSpotLight(this);
		castsShadow = true;
	}

	Lighting3D::Lighting3D()
	{
	}

	Lighting3D::~Lighting3D()
	{
		for (size_t i = 0; i < m_spotLights.size(); i++)
		{
			delete m_spotLights[i];
		}
		m_spotLights.clear();
		for (size_t i = 0; i < m_directionalLights.size(); i++)
		{
			delete m_directionalLights[i];
		}
		m_directionalLights.clear();
		for (size_t i = 0; i < m_pointLights.size(); i++)
		{
			delete m_pointLights[i];
		}
		m_pointLights.clear();
	}

	void Lighting3D::load(Shader* s, GLuint shadowMapStartIndex, const std::string & spotLightName, const std::string & directionalLightsName, const std::string & pointLightName)
	{
		for (size_t i = 0; i < m_spotLights.size(); i++)
		{
			m_spotLights[i]->load(s, i, true, spotLightName, shadowMapStartIndex++);
		}
		for (size_t i = 0; i < m_directionalLights.size(); i++)
		{
			m_directionalLights[i]->load(s, i, true, directionalLightsName, shadowMapStartIndex++);
		}
		for (size_t i = 0; i < m_pointLights.size(); i++)
		{
			m_pointLights[i]->load(s, i, true, pointLightName, shadowMapStartIndex++);
		}
	}

	void Lighting3D::renderShadowMaps(MainClass* m, Shader* s)
	{
		for (size_t i = 0; i < m_spotLights.size(); i++)
		{
			if (m_spotLights[i]->castsShadow)
				m_spotLights[i]->shadowMap->render(m, s);
		}
		for (size_t i = 0; i < m_directionalLights.size(); i++)
		{
			if (m_directionalLights[i]->castsShadow)
				m_directionalLights[i]->shadowMap->render(m, s);
		}
		for (size_t i = 0; i < m_pointLights.size(); i++)
		{
			if (m_pointLights[i]->castsShadow)
				m_pointLights[i]->shadowMap->render(m, s);
		}
	}

	void Lighting3D::addLight(SpotLight3D* s)
	{
		m_spotLights.push_back(s);
	}

	void Lighting3D::addLight(DirectionalLight3D* d)
	{
		m_directionalLights.push_back(d);
	}

	void Lighting3D::addLight(PointLight3D* p)
	{
		m_pointLights.push_back(p);
	}

	std::map<std::string, std::string> Lighting3D::getDefineChanges(const std::string & numSpotLights, const std::string & numDirectionalLights, const std::string & numPointLights) const
	{
		std::map<std::string, std::string> defines;
		std::stringstream stream;
		std::string numS, numD, numP;

		stream << m_spotLights.size();
		stream >> numS;
		stream.clear();
		stream << m_directionalLights.size();
		stream >> numD;
		stream.clear();
		stream << m_pointLights.size();
		stream >> numP;
		stream.clear();

		defines[numSpotLights] = numS;
		defines[numDirectionalLights] = numD;
		defines[numPointLights] = numP;

		return defines;
	}

}