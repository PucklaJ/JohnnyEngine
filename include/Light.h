#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

class Shader;
class ShadowMap;

namespace SDL
{
	class MainClass;
}

class PointLight
{
public:
	static void load(Shader*,PointLight*,unsigned int,const std::string& name = "pointLights", GLuint shadowMapStartIndex = 0);

	PointLight() {}
	PointLight(const glm::vec3&, const glm::vec3& _diffuse = glm::vec3(1.0,1.0,1.0), const glm::vec3& _specular = glm::vec3(1.0,1.0,1.0), GLfloat _quadratic = 0.001, GLfloat _linear = 0.1, GLfloat _constant = 0.5);
	~PointLight();

	void load(Shader*,GLuint index = 0,bool isArray = true,const std::string& name = "pointLights", GLuint shadowMapIndex = 0);
	void setShadowMap(GLsizei, GLsizei);

	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat quadratic;
	GLfloat linear;
	GLfloat constant;
	ShadowMap* shadowMap = nullptr;
	bool castsShadow = false;
};

class DirectionalLight
{
public:
	static void load(Shader*, DirectionalLight*, unsigned int, const std::string& name = "directionalLights", GLuint shadowMapStartIndex = 0);

	DirectionalLight() {}
	DirectionalLight(const glm::vec3&, const glm::vec3& _diffuse = glm::vec3(1.0, 1.0, 1.0), const glm::vec3& _specular = glm::vec3(1.0, 1.0, 1.0));
	~DirectionalLight();

	void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "directionalLights", GLuint shadowMapIndex = 0);
	void setShadowMap(GLsizei, GLsizei);

	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
	ShadowMap* shadowMap = nullptr;
	bool castsShadow = false;
};

class SpotLight
{
public:
	static void load(Shader*, SpotLight*, unsigned int, const std::string& name = "spotLights", GLuint shadowMapStartIndex = 0);

	SpotLight() {}
	SpotLight(const glm::vec3&,const glm::vec3&,GLfloat,GLfloat,const glm::vec3& _diffuse = glm::vec3(1.0, 1.0, 1.0), const glm::vec3& _specular = glm::vec3(1.0, 1.0, 1.0), GLfloat _quadratic = 0.001, GLfloat _linear = 0.1, GLfloat _constant = 0.5);
	~SpotLight();

	void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "spotLights",GLuint shadowMapIndex = 0);
	void setShadowMap(GLsizei, GLsizei);

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat innerCutOff;
	GLfloat outerCutOff;
	GLfloat quadratic;
	GLfloat linear;
	GLfloat constant;
	ShadowMap* shadowMap = nullptr;
	bool castsShadow = false;
};

class Lighting
{
public:
	static glm::vec4 ambientLight;

	Lighting();
	~Lighting();

	void load(Shader*, GLuint shadowMapStartIndex = 0,const std::string& spotLightName = "spotLights", const std::string& directionalLightsName = "directionalLights", const std::string& pointLightName = "pointLights");
	void renderShadowMaps(SDL::MainClass*,Shader*);

	void addLight(SpotLight*);
	void addLight(DirectionalLight*);
	void addLight(PointLight*);
	
	std::map<std::string,std::string> getDefineChanges(const std::string& numSpotLights = "NUM_SPOT_LIGHTS",const std::string& numDirectionalLights = "NUM_DIRECTIONAL_LIGHTS",const std::string& numPointLights = "NUM_POINT_LIGHTS") const;

	const std::vector<SpotLight*>& getSpotLights() const { return m_spotLights; }
	const std::vector<DirectionalLight*>& getDirectionalLights() const { return m_directionalLights; }
	const std::vector<PointLight*>& getPointLights() const { return m_pointLights; }

private:
	std::vector<SpotLight*> m_spotLights;
	std::vector<DirectionalLight*> m_directionalLights;
	std::vector<PointLight*> m_pointLights;
};

#endif

