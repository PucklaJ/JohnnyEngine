#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <SDL2/SDL.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Geometry.h"
#include "ShaderUpdater.h"
#include "Colors.h"


namespace Johnny
{
	class MainClass;
	class Shader;
	class Mesh3D;
	class Camera2D;
    class Sprite2D;
    class Camera3D;
    class Lighting3D;
    
    enum DrawModes
    {
      DIRECT=0,
      BLENDING=1
    };
    
    class Texture2DShaderUpdater : public ShaderUpdater
    {
    public:
        static const unsigned int TRANSFORM_NORMAL;
        static const unsigned int TRANSFORM_CAMERA;
    
        Texture2DShaderUpdater(Shader* s) : ShaderUpdater(s) {};
        ~Texture2DShaderUpdater();
        
        void update() override;
        
        void setUniforms(Camera3D*,const unsigned int index = 0) override {}
        void setUniforms(Lighting3D*,const unsigned int index = 0) override {}
        
        void setUniforms(Transform2D*,const unsigned int index = 0) override;
        void setUniforms(Texture*,const unsigned int index = 0) override;
        void setUniforms(TextureRegion*,const unsigned int index = 0) override;
        void setUniforms(Sprite2D*,const unsigned int index = 0) override;
    };

	class Texture
	{
	public:
		static Mesh3D* createTexturePlane(GLfloat, GLfloat);
		static Texture* SDL_SurfaceToTexture(SDL_Surface*,GLenum filtering = GL_LINEAR);
		static void initTexture2DShader(MainClass*);
		static void initTexture2DBuffers();
		static void renderTexture2D(Texture*, const Matrix3f&,const TextureRegion* srcRegion = nullptr, bool bindShader = true,bool isFrameBuffer = false);
		static void renderTexture2D(Texture*, const Vector2f&, const Vector2f& scale = Vector2f(1.0f,1.0f), const GLfloat& rotation = 0.0f, const Camera2D* cam = nullptr,const TextureRegion* srcRegion = nullptr, bool bindShader = true,bool isFrameBuffer = false,GLenum target = GL_TEXTURE_2D);
        static void renderTexture2D(Texture*, const TextureRegion* dst = nullptr, const TextureRegion* src = nullptr,const GLfloat& rotation = 0.0f,const Camera2D* cam = nullptr,bool bindShader = true, bool isFrameBuffer = false);
        static void renderSprite2D();
        
        static Texture* BOX(const Vector2i&,const Colorf& color = Colorf(0.0f,0.0f,0.0f,0.0f),GLenum target = GL_TEXTURE_2D,GLenum filtering = GL_LINEAR,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE);
        
		static Shader* getTexture2DShader();

		Texture(GLubyte*, GLsizei, GLsizei,GLenum,GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE, GLenum target = GL_TEXTURE_2D);
		Texture();
		~Texture();

		void bind(Shader*, const std::string& name = "textureAddress", GLuint unit = 0, GLenum target = GL_TEXTURE_2D);
		void unbind(GLuint unit = 0, GLenum target = GL_TEXTURE_2D);
        GLubyte* readPixels(GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);
        SDL_Surface* toSDLSurface(GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE);
        
        void setKeyColor(const Colorb& color) {m_keyColor=color;}
        void setModColor(const Colorb& color) {m_modColor=color;}
        void setDrawMode(const DrawModes& mode) {m_drawMode=mode;}
        
		GLuint getBuffer() { return m_texture; }
		const GLsizei& getWidth();
		const GLsizei& getHeight();
        
        const Colorb& getKeyColor() const {return m_keyColor;}
        const Colorb& getModColor() const {return m_modColor;}
        const DrawModes& getDrawMode() const {return m_drawMode;}

	protected:
		static Shader* m_texture2DShader;
		static GLuint m_texture2D_vbo;
		static GLuint m_texture2D_vao;

		GLuint m_texture = 0;
		GLsizei m_width = 0;
		GLsizei m_height = 0;
        Colorb m_keyColor;
        Colorb m_modColor = Colorb(255,255,255,255);
        DrawModes m_drawMode = BLENDING;

	};
}

#endif

