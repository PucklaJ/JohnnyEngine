#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <vector>
#include <string>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <SDL2/SDL_surface.h>



namespace Johnny
{
	class MainClass;
	class Texture;
	class Mesh3D;
	class Model3D;
	class SpotLight3D;
	class DirectionalLight3D;
	class PointLight3D;

	class Scene
	{
	public:
		void addAsEntities(MainClass*);

		Model3D* getModel(const std::string&);

		std::vector<Model3D*> models;
		std::vector<SpotLight3D*> spotLights;
		std::vector<DirectionalLight3D*> directionalLights;
		std::vector<PointLight3D*> pointLights;
	};

	class TextureData
	{
	public:
		~TextureData();

		GLubyte* data = nullptr;
		GLsizei width = 0;
		GLsizei height = 0;
		GLint numChannels = 0;
        
        Texture* toTexture(GLenum target = GL_TEXTURE_2D,GLenum filtering = GL_LINEAR,GLenum format = GL_RGBA);
        SDL_Surface* toSDL_Surface(Uint32 pixelFormat = SDL_PIXELFORMAT_RGBA8888);
	};

    class ResourceManager
    {
        public:
            ResourceManager();
            virtual ~ResourceManager();

            Texture* loadTexture(const std::string&,GLenum filtering = GL_LINEAR);
			TextureData* loadTextureData(const std::string&);
			std::string loadShader(const std::string&,std::map<std::string,std::string>* defineChanges = nullptr);
			Mesh3D* loadMesh(const std::string&);
			Scene* loadScene(const std::string&);
            
            void clearTextures();
            void deleteTexture(Texture*);
			void clearTextureDatas();
			void deleteTextureData(TextureData*);
			void clearShaders();
			void clearMeshes();
			void deleteMesh(Mesh3D*);
			void clearScenes();
			void deleteScene(Scene*);
            
            bool isLoaded(Texture*);
			bool isLoaded(Mesh3D*);
			bool isLoaded(Scene*);
			bool isLoaded(TextureData*);
            
            void clear();


        protected:

        private:
			void processScene(const aiScene*, Scene*,bool);
			void processNode(aiNode*, const aiScene*, Scene*,bool);

			std::string getFileName(const std::string&);

            std::map<std::string,Texture*> m_textures;
			std::map<std::string, TextureData*> m_textureBytes;
			std::map<std::string, std::string> m_shaders;
			std::map<std::string, Mesh3D*> m_meshes;
			std::map<std::string, Scene*> m_scenes;

    };
}



#endif // RESOURCEMANAGER_H
