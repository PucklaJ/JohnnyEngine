#include "Texture.h"
#include <GL/glew.h>
#include "Geometry.h"

namespace Johnny
{
    class FrameBuffer;
    class Camera2D;
    
    class RenderTexture : public Texture
    {
    public:
        RenderTexture(GLsizei,GLsizei,GLenum filtering = GL_LINEAR,GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE);
        ~RenderTexture();
        
        void target();
        void untarget();
        void render(const Vector2f&,const Vector2f& scale = Vector2f(1.0f,1.0f),GLfloat rotation = 0.0f, const Camera2D* cam = nullptr,const TextureRegion* srcRegion = nullptr, bool bindShader = true);
        
        FrameBuffer* getFrameBuffer() {return m_frameBuffer;}
    
    private:
        FrameBuffer* m_frameBuffer = nullptr;
        
    };
}