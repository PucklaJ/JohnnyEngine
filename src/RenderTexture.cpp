#include "../include/RenderTexture.h"
#include "../include/FrameBuffer.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/Transform2D.h"

namespace Johnny
{
    RenderTexture::RenderTexture(GLsizei width,GLsizei height,GLenum filtering,GLenum target,GLenum format,GLenum type) :
        Texture(nullptr,width,height,filtering,format,format,type,target)
    {
        m_frameBuffer = new FrameBuffer();
        m_frameBuffer->addTexture(this,GL_COLOR_ATTACHMENT0,GL_FRAMEBUFFER,target);
        if(!m_frameBuffer->checkStatus())
            LogManager::error("FrameBuffer of RenderTexture isn't completed");
    }
    
    RenderTexture::~RenderTexture()
    {
        delete m_frameBuffer;
    }
    
    void RenderTexture::target()
    {
        m_frameBuffer->bind();
        glViewport(0,0,getWidth(),getHeight());
        TransformableObject2D::setViewportSize(Vector2f(getWidth(),getHeight()));
    }
    
    void RenderTexture::untarget()
    {
        MainClass::getInstance()->getBackBuffer()->bind();
        glViewport(0,0,MainClass::getInstance()->getNativeRes().x,MainClass::getInstance()->getNativeRes().y);
        TransformableObject2D::setViewportSize(MainClass::getInstance()->getNativeRes());
    }
    
    void RenderTexture::render(const Vector2f& position,const Vector2f& scale,GLfloat rotation, const Camera2D* cam,const TextureRegion* srcRegion, bool bindShader,GLenum target)
    {
        renderTexture2D(this,position,scale,rotation,cam,srcRegion,bindShader,true,target);
    }
}