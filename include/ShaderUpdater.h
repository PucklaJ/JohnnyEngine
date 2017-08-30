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
    
    /*! \brief A class which is used to update the uniforms of a Shader
     *
     */
    class ShaderUpdater
    {
    public:
        static const unsigned int TRANSFORM_NORMAL; //!< The index to indicate that a normal transform should be loaded
        static const unsigned int TRANSFORM_CAMERA; //!< The index to indicate that a camera transformed transform should be loaded
        static const unsigned int TRANSFORM_WORLD;  //!< The index to indicate that a world transform should be loaded;
        
        /*! \brief Creates a new ShaderUpdater
         *  \param s The shader which should be updated
         */
        ShaderUpdater(Shader* s);
        ~ShaderUpdater();
        
        /*! \brief Gets called every frame before anything is rendered
         *
         */
        virtual void update(){}
        
        /*! \brief Gets called every time a Mesh3D gets rendered
         *  \param mesh The Mesh3D which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Mesh3D* mesh,const unsigned int index = 0);
        /*! \brief Gets called every time a Model3D gets rendered
         *  \param model The Model3D which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Model3D* model,const unsigned int index = 0);
        /*! \brief Sets the uniforms for a Lighting3D
         *  \param light The Lighting3D to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Lighting3D* light,const unsigned int index = 0);
        /*! \brief Sets the uniforms for a Camera3D
         *  \param cam The Camera3D to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Camera3D* cam,const unsigned int index = 0);
        /*! \brief Sets the uniforms for a Transform3D
         *  \param transform The Transform3D to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Transform3D* transform,const unsigned int index = 0);
        /*! \brief Sets the uniforms for a Material
         *  \param mat The Material to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Material* mat,const unsigned int index = 0);
        
        /*! \brief Sets the uniforms for a Transform2D
         *  \param transform The Transform2D to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Transform2D* transform,const unsigned int index = 0){}
        /*! \brief Sets the uniforms for a TextureRegion
         *  \param region The TextureRegion to set the uniforms for
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(TextureRegion* region,const unsigned int index = 0){}
        
        /*! \brief Gets called every time a Textrue gets rendered (unsused)
         *  \param tex The tex which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Texture* tex,const unsigned int index = 0){}
        
        /*! \brief Gets called every time a Entity3D gets rendered
         *  \param ent The Entity3D which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Entity3D* ent,const unsigned int index = 0);
        /*! \brief Gets called every time a Sprite2D gets rendered
         *  \param spr The Sprite2D which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Sprite2D* spr,const unsigned int index = 0){}
        /*! \brief Gets called every time a Skybox gets rendered
         *  \param sky The Skybox which should be rendered
         *  \param index The index of the function to make it possible to use multiple versions of the function
         */
        virtual void setUniforms(Skybox* sky,const unsigned int index = 0){}
        
    protected:
        Shader* m_shader = nullptr; //!< The Shader which should be updated
    };
}

#endif