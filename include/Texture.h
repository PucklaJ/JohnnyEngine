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
    
    /*! \brief An enum which defines a few modes how a Texture will be blended
     *
     */
    enum DrawModes
    {
      DIRECT=0,  //!< No blending
      BLENDING=1 //!< Normal blending
    };
    
    enum Flip
    {
      NONE=0,
      HORIZONTALLY=1,
      VERTICALLY=2,
      DIAGONALLY=3
    };
    
    /*! \brief The ShaderUpdater for the Texture2DShader
     *
     */
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

    /*! \brief A class which represents a texture on the graphics card
     *
     */
	class Texture
	{
	public:
        /*! \brief Creates a plane mesh
         *  \param width The width of the plane
         *  \param height The height of the plane
         */
		static Mesh3D* createTexturePlane(GLfloat width, GLfloat height);
        /*! \brief Converts a SDL_Surface into a Texture
         *  \param sur The SDL_Surface to convert
         *  \param filtering The filter method which will be applied to the new Texture
         */
		static Texture* SDL_SurfaceToTexture(SDL_Surface* sur,GLenum filtering = GL_LINEAR);
        /*! \brief Initialises the Texture2DShader which is used for rendering textures
         *  \param m The MainClass from which to load the source files
         */
		static void initTexture2DShader(MainClass* m);
        /*! \brief Initialises The buffers of the mesh which is used for rendering textures
         *
         */
		static void initTexture2DBuffers();
        /*! \brief Renderes a texture as a 2D plane on the currently active frame buffer
         *  \param transform The transformation matrix to apply to the Texture (center is in the middle of the screen)
         *  \param tex The Texture to render
         *  \param srcRegion The TextureRegion ehich defines what to use from the Texture (if nullptr then {0,0,width,height} will be used)
         *  \param bindShader Defines wether the Texture2DShaer should be bound
         *  \param isFrameBuffer Set this to true if a FrameBuffer wasa used to render on the Texture you want to render
         *  \param depth The dept with which the Texture will be rendered (Textures with a smaller depth value are rendered above [-INT_MAX;INT_MAX])
         */
		static void renderTexture2D(Texture* tex, const Matrix3f& transform,const TextureRegion* srcRegion = nullptr, bool bindShader = true,bool isFrameBuffer = false,int depth = 0);
         /*! \brief Renderes a texture as a 2D plane on the currently active frame buffer
         *   \param tex The Texture to render
         *   \param position The position to which to render the Texture (leftup corner, center is in the leftup corner of the window)
         *   \param scale The scale which will be applied to the Texture
         *   \param rotaion The amount whic hthe Texture will be rotated
         *   \param cam The Camera2D in which view the Texture should b transformed (if nullptr no view transformation will be applied)
         *   \param srcRegion The TextureRegion ehich defines what to use from the Texture (if nullptr then {0,0,width,height} will be used)
         *   \param bindShader Defines wether the Texture2DShaer should be bound
         *   \param isFrameBuffer Set this to true if a FrameBuffer wasa used to render on the Texture you want to render
         *   \param target The target to which The Textrue should be bound
         *   \param depth The dept with which the Texture will be rendered (Textures with a smaller depth value are rendered above [-INT_MAX;INT_MAX])
         */
		static void renderTexture2D(Texture* tex, const Vector2f& position, const Vector2f& scale = Vector2f(1.0f,1.0f), const GLfloat& rotation = 0.0f, const Camera2D* cam = nullptr,const TextureRegion* srcRegion = nullptr, bool bindShader = true,bool isFrameBuffer = false,GLenum target = GL_TEXTURE_2D,int depth = 0);
        /*! \brief Renderes a texture as a 2D plane on the currently active frame buffer
         *   \param tex The Texture to render
         *   \param dst The TextureRegion which defines where and how big to render the Texture (if nullptr {0,0,screenWidth,screenHeight} will be used)
         *   \param src The TextureRegion which defines what to use from the Texture (if nullptr {0,0,width,height} will be used)
         *   \param rotaion The amount whic hthe Texture will be rotated
         *   \param cam The Camera2D in which view the Texture should b transformed (if nullptr no view transformation will be applied)
         *   \param srcRegion The TextureRegion ehich defines what to use from the Texture (if nullptr then {0,0,width,height} will be used)
         *   \param bindShader Defines wether the Texture2DShaer should be bound
         *   \param isFrameBuffer Set this to true if a FrameBuffer wasa used to render on the Texture you want to render
         *   \param depth The dept with which the Texture will be rendered (Textures with a smaller depth value are rendered above [-INT_MAX;INT_MAX])
         */
        static void renderTexture2D(Texture* tex, const TextureRegion* dst = nullptr, const TextureRegion* src = nullptr,const GLfloat& rotation = 0.0f,const Camera2D* cam = nullptr,bool bindShader = true, bool isFrameBuffer = false,int depth = 0);
        /*! \brief Just draws the buffer
         *
         */
        static void renderSprite2D();
        
        /*! \brief Creates a rectangular Texture
         *  \param size The size if the Texture in pixels
         *  \param color The color of the Texture
         *  \param target The target to which the Texture should be bound
         *  \param filtering The filter method which will be applied to the Texture
         *  \param format The format of the Texture with which the pixels should be stored
         *  \param type The type of each color channel
         */
        static Texture* BOX(const Vector2i& size,const Colorf& color = Colorf(0.0f,0.0f,0.0f,0.0f),GLenum target = GL_TEXTURE_2D,GLenum filtering = GL_LINEAR,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE);
        
        /*! \return The Shader which will be used for rendering Textures
         *
         */
		static Shader* getTexture2DShader();

        /*! \Creates a new Texture
         *  \param pixels The pixel data of the new Texture
         *  \param width The width of the new Texture in pixels
         *  \param height The height of the new Texture in pixels
         *  \param filtering The filter method which will be applied to the new Texture
         *  \param internalFormat The format in which the pixels are stored
         *  \param format The format in which the pixel data is stored
         *  \param type The type in which the pixel dara is stored
         *  \param target The target to which the Texture will be bound
         */
		Texture(GLubyte* pixels, GLsizei width, GLsizei height,GLenum filtering,GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE, GLenum target = GL_TEXTURE_2D);
		/*! \Creates a new Texture
         *  \param texture The name of the texture (or ID)
         *  \param width The width of the texture in pixels
         *  \param height The height of the texture in pixels
         */
        Texture(GLuint texture,GLsizei width, GLsizei height);
        /*! \Creates a new Texture
         *
         */
        Texture();
		~Texture();
 
        /*! \brief Binds a Texture and loads it as a uniform to a Shader
         *  \param s The Shader to which to load the Texture as a uniform
         *  \param name The name of the uniform
         *  \param unit The texture unit to which the Textrue will be bound (GL_TEXTURE0+unit)
         *  \param target The target to which the Texture will be bound
         */
		void bind(Shader* s, const std::string& name = "textureAddress", GLuint unit = 0, GLenum target = GL_TEXTURE_2D);
        /*! \brief Unbinds a Texture
         *  \param unit The texture unit to which the Texture will be bound
         *  \param target The target from which the Texture will be unbound
         */
		void unbind(GLuint unit = 0, GLenum target = GL_TEXTURE_2D);
        /*! \brief Reads the pixels int the RAM
         *  \param target The target to which the Texture will be bound
         *  \param format The format in which the pixels are stored
         *  \param type The type with which the color channels are stored
         *  \return The pixel data of the Texture
         */
        GLubyte* readPixels(GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);
        /*! \brief Converts the Texture to a SDL_Surface
         *  \param target The target to which the Texture should be bound
         *  \param format The format in which the pixels are stored
         *  \param type The type in which the color channels are stored
         *  \return The Texture as a SDL_Surface
         */
        SDL_Surface* toSDLSurface(GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE);
        
        /*! \brief Sets color which should be keyd from the Texture
         *  \param color The color to key
         */
        void setKeyColor(const Colorb& color) {m_keyColor=color;}
        /*! \brief Sets the color with which the texture will be multiplied
         *  \param color The color with which it will be multiplied
         */
        void setModColor(const Colorb& color) {m_modColor=color;}
        /*! \brief Sets the mode of how to blend the Texture
         *  \param mode The mode to blend
         */
        void setDrawMode(const DrawModes& mode) {m_drawMode=mode;}
        
        /*! \brief Sets the flip of a Texture
         *  \param flip The Flip to set
         */
        void setFlip(const Flip& flip) {m_flip=flip;}
        
        /*! \return The name of the texture
         *
         */
		GLuint getBuffer() { return m_texture; }
        /*! \return The width of the Texture in pixels
         *
         */
		const GLsizei& getWidth();
        /*! \return The height of the Texture in pixels
         *
         */
		const GLsizei& getHeight();
        
        /*! \return The color which should be keyd from the Texture
         *
         */
        const Colorb& getKeyColor() const {return m_keyColor;}
        /*! \return The color with which the Texture will be multiplied
         *
         */
        const Colorb& getModColor() const {return m_modColor;}
        /*! \return The mode with which the Texture will be blended
         *
         */
        const DrawModes& getDrawMode() const {return m_drawMode;}
        
        /*! \return The flip which defines how a Texture should be flipped 
         * 
         */
        const Flip& getFlip() const {return m_flip;}

	protected:
		static Shader* m_texture2DShader; //!< The Shader which will be used for rendering textures as 2D planes
		static GLuint m_texture2D_vbo;    //!< The name of the vertex buffer object which is used for rendering textures
		static GLuint m_texture2D_vao;    //!< The vertex array object which is used for rendering textures

		GLuint m_texture = 0;                        //!< The name of the Texture
		GLsizei m_width = 0;                         //!< The width of the Texture in pixels
		GLsizei m_height = 0;                        //!< The height of the Texture in pixels
        Colorb m_keyColor;                           //!< The color which should be keyd from the Texture
        Colorb m_modColor = Colorb(255,255,255,255); //!< The color with which the Texture should be multiplied
        DrawModes m_drawMode = BLENDING;             //!< The mode with which the Texture will be blended
        Flip m_flip = NONE;                          //!< The flip which defines how a Texture should be flipped

	};
}

#endif

