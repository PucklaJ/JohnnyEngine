#ifndef SHADER_UPDATER_H
#define SHADER_UPDATER_H
#include "Geometry.h"

namespace Johnny
{
    class Shader;
    
    class Mesh3D;
    class Model3D;
    class Lighting3D;
    class Camera3D;
    class Transform3D;
    class Material;
    class Entity3D;
    class Sprite2D;
    class Skybox;
    
    class Transform2D;
    
    class Texture;
    
    class ShaderUpdater
    {
    public:
        static const unsigned int TRANSFORM_NORMAL;
        static const unsigned int TRANSFORM_CAMERA;
        static const unsigned int TRANSFORM_WORLD;
    
        ShaderUpdater(Shader*);
        ~ShaderUpdater();
        
        virtual void update(){}
        
        virtual void setUniforms(Mesh3D*,const unsigned int index = 0);
        virtual void setUniforms(Model3D*,const unsigned int index = 0);
        virtual void setUniforms(Lighting3D*,const unsigned int index = 0);
        virtual void setUniforms(Camera3D*,const unsigned int index = 0);
        virtual void setUniforms(Transform3D*,const unsigned int index = 0);
        virtual void setUniforms(Material*,const unsigned int index = 0);
        
        virtual void setUniforms(Transform2D*,const unsigned int index = 0){}
        virtual void setUniforms(TextureRegion*,const unsigned int index = 0){}
        
        virtual void setUniforms(Texture*,const unsigned int index = 0){}
        
        virtual void setUniforms(Entity3D*,const unsigned int index = 0);
        virtual void setUniforms(Sprite2D*,const unsigned int index = 0){}
        virtual void setUniforms(Skybox*,const unsigned int index = 0){}
        
    protected:
        Shader* m_shader = nullptr;
    };
}

#endif