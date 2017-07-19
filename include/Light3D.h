#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

namespace Johnny
{
	class Shader;
	class ShadowMap3D;
	class MainClass;

	class PointLight3D
	{
	public:
		static void load(Shader*, PointLight3D*, unsigned int, const std::string& name = "pointLights", GLuint shadowMapStartIndex = 0);

		PointLight3D() {}
		PointLight3D(const glm::vec3&, const glm::vec3& _diffuse = glm::vec3(1.0, 1.0, 1.0), const glm::vec3& _specular = glm::vec3(1.0, 1.0, 1.0), GLfloat _quadratic = 0.001, GLfloat _linear = 0.1, GLfloat _constant = 0.5);
		~PointLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "pointLights", GLuint shadowMapIndex = 0);
		void setShadowMap(GLsizei, GLsizei);

		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 specular;
		GLfloat quadratic;
		GLfloat linear;
		GLfloat constant;
		ShadowMap3D* shadowMap = nullptr;
		bool castsShadow = false;
	};

	class DirectionalLight3D
	{
	public:
		static void load(Shader*, DirectionalLight3D*, unsigned int, const std::string& name = "directionalLights", GLuint shadowMapStartIndex = 0);

		DirectionalLight3D() {}
		DirectionalLight3D(const glm::vec3&, const glm::vec3& _diffuse = glm::vec3(1.0, 1.0, 1.0), const glm::vec3& _specular = glm::vec3(1.0, 1.0, 1.0));
		~DirectionalLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "directionalLights", GLuint shadowMapIndex = 0);
		void setShadowMap(GLsizei, GLsizei);

		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
		ShadowMap3D* shadowMap = nullptr;
		bool castsShadow = false;
	};

	class SpotLight3D
	{
	public:
		static void load(Shader*, SpotLight3D*, unsigned int, const std::string& name = "spotLights", GLuint shadowMapStartIndex = 0);

		SpotLight3D() {}
		SpotLight3D(const glm::vec3&, const glm::vec3&, GLfloat, GLfloat, const glm::vec3& _diffuse = glm::vec3(1.0, 1.0, 1.0), const glm::vec3& _specular = glm::vec3(1.0, 1.0, 1.0), GLfloat _quadratic = 0.001, GLfloat _linear = 0.1, GLfloat _constant = 0.5);
		~SpotLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "spotLights", GLuint shadowMapIndex = 0);
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
		ShadowMap3D* shadowMap = nullptr;
		bool castsShadow = false;
	};

	class Lighting3D
	{
	public:
		static glm::vec4 ambientLight;

		Lighting3D();
		~Lighting3D();

		void load(Shader*, GLuint shadowMapStartIndex = 0, const std::string& spotLightName = "spotLights", const std::string& directionalLightsName = "directionalLights", const std::string& pointLightName = "pointLights");
		void renderShadowMaps(MainClass*, Shader*);

		void addLight(SpotLight3D*);
		void addLight(DirectionalLight3D*);
		void addLight(PointLight3D*);

		std::map<std::string, std::string> getDefineChanges(const std::string& numSpotLights = "NUM_SPOT_LIGHTS", const std::string& numDirectionalLights = "NUM_DIRECTIONAL_LIGHTS", const std::string& numPointLights = "NUM_POINT_LIGHTS") const;

		const std::vector<SpotLight3D*>& getSpotLights() const { return m_spotLights; }
		const std::vector<DirectionalLight3D*>& getDirectionalLights() const { return m_directionalLights; }
		const std::vector<PointLight3D*>& getPointLights() const { return m_pointLights; }

	private:
		std::vector<SpotLight3D*> m_spotLights;
		std::vector<DirectionalLight3D*> m_directionalLights;
		std::vector<PointLight3D*> m_pointLights;
	};
}

#endif
