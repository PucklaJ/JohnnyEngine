#pragma once
#include "../include/Actor.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "ShaderUpdater.h"

namespace Johnny
{
	class CubeMap3D;
	class Shader;
    
    class SkyboxShaderUpdater : public ShaderUpdater
    {
    public:
        SkyboxShaderUpdater(Shader* s) : ShaderUpdater(s) {}
        ~SkyboxShaderUpdater(){}
        
        void setUniforms(Skybox*,const unsigned int index = 0) override;
        void setUniforms(Lighting3D*,const unsigned int index = 0) override {}
        void setUniforms(Camera3D*,const unsigned int index = 0) override;
    };

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

		void addVertices(SkyboxVertex*, unsigned int);

		void render();
	private:
		GLuint m_vbo = 0;
		GLuint m_vao = 0;

		GLsizei m_numVertices = 0;
	};

	enum SkyboxTex : unsigned int
	{
		RIGHT=0,
		LEFT=1,
		TOP=2,
		BOTTOM=3,
		FRONT=4,
		BACK=5
	};

	class Skybox : public Actor
	{
	public:
        friend class SkyboxShaderUpdater;
        
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

		CubeMap3D* m_cubeMap = nullptr;
		std::string m_textures[6];
        bool m_texturesSet = false;
	};
}

