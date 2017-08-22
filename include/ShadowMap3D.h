#pragma once
#include "Texture.h"
#include "Matrix4.h"
#include "ShaderUpdater.h"
#include <string>

#define SHADOW_POINT 1
#define SHADOW_DIR 2
#define SHADOW_SPOT 3



namespace Johnny
{
	class MainClass;
	class FrameBuffer;
	class PointLight3D;
	class DirectionalLight3D;
	class SpotLight3D;
	class Shader;
    class Entity3D;
    
    class ShadowMap3DShaderUpdater : public ShaderUpdater
    {
    public:
        ShadowMap3DShaderUpdater(Shader* s) : ShaderUpdater(s) {}
        ~ShadowMap3DShaderUpdater() {}
        
        void setUniforms(Camera3D*,const unsigned int index = 0) override {}
        void setUniforms(Lighting3D*,const unsigned int index = 0) override {}
        void setUniforms(Mesh3D*,const unsigned int index = 0) override {}
        
        void setUniforms(Transform3D*,const unsigned int index = 0) override;
        void setUniforms(Entity3D*,const unsigned int index = 0) override;
        
    };

	class ShadowMap3D : public Texture
	{
	public:
		ShadowMap3D(GLsizei, GLsizei);
		~ShadowMap3D();

		void render(MainClass*, Shader*);

		void setPointLight(PointLight3D*);
		void setDirectionalLight(DirectionalLight3D*);
		void setSpotLight(SpotLight3D*);
		void loadMatrix(Shader*, const std::string& name = "lightSpaceMatrix");
		void load(Shader*, GLuint index = 0, const std::string& matrixName = "lightSpaceMatrix", const std::string& textureName = "shadowMap");

		FrameBuffer* getFrameBuffer() { return m_frameBuffer; }
	private:
		void configureMatricesAndShader(Shader*);

		GLsizei m_width;
		GLsizei m_height;
		FrameBuffer* m_frameBuffer = nullptr;
		PointLight3D* m_pointLight = nullptr;
		DirectionalLight3D* m_directionalLight = nullptr;
		SpotLight3D* m_spotLight = nullptr;
		GLuint m_curLight = 0;

		Matrix4f m_lightSpaceMatrix;
	};

}
