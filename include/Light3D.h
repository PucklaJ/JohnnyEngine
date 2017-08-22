#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "Vector4.h"
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include "Colors.h"

namespace Johnny
{
	class Shader;
	class ShadowMap3D;
	class MainClass;

	class PointLight3D
	{
	public:
		static void load(Shader*, PointLight3D*, unsigned int, const std::string& name = "pointLights", GLuint shadowMapStartIndex = 0);

		PointLight3D() : PointLight3D(Vector3f(0.0f,0.0f,0.0f)) {}
		PointLight3D(const Vector3f&, const Colorb& _diffuse = Colorb(255, 255, 255), const Colorb& _specular = Colorb(255, 255, 255), GLfloat _quadratic = 0.001f, GLfloat _linear = 0.1f, GLfloat _constant = 0.5f);
		~PointLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "pointLights", GLuint shadowMapIndex = 0);
		void setShadowMap(GLsizei, GLsizei);

		Vector3f position;
		Colorb diffuse;
		Colorb specular;
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

		DirectionalLight3D() : DirectionalLight3D(Vector3f(0.0f,0.0f,-1.0f)) {}
		DirectionalLight3D(const Vector3f&, const Colorb& _diffuse = Colorb(255, 255, 255), const Colorb& _specular = Colorb(255, 255, 255));
		~DirectionalLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "directionalLights", GLuint shadowMapIndex = 0);
		void setShadowMap(GLsizei, GLsizei);

		Vector3f direction;
		Colorb diffuse;
		Colorb specular;
		ShadowMap3D* shadowMap = nullptr;
		bool castsShadow = false;
	};

	class SpotLight3D
	{
	public:
		static void load(Shader*, SpotLight3D*, unsigned int, const std::string& name = "spotLights", GLuint shadowMapStartIndex = 0);

		SpotLight3D() : SpotLight3D(Vector3f(0.0f,0.0f,0.0f),Vector3f(0.0f,0.0f,-1.0f),30.0f,50.0f) {}
		SpotLight3D(const Vector3f&, const Vector3f&, GLfloat, GLfloat, const Colorb& _diffuse = Colorb(255, 255, 255), const Colorb& _specular = Colorb(255, 255, 255), GLfloat _quadratic = 0.001f, GLfloat _linear = 0.1f, GLfloat _constant = 0.5f);
		~SpotLight3D();

		void load(Shader*, GLuint index = 0, bool isArray = true, const std::string& name = "spotLights", GLuint shadowMapIndex = 0);
		void setShadowMap(GLsizei, GLsizei);

		Vector3f position;
		Vector3f direction;
		Colorb diffuse;
		Colorb specular;
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
		static Colorb ambientLight;

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
