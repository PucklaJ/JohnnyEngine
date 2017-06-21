#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <vector>
#include <string>
#include <assimp/scene.h>
#include <GL/glew.h>

class Texture;
class Mesh;
class Model;
class SpotLight;
class DirectionalLight;
class PointLight;

namespace SDL
{
	class MainClass;
}

class Scene
{
public:
	void addAsEntities(SDL::MainClass*);

	Model* getModel(const std::string&);

	std::vector<Model*> models;
	std::vector<SpotLight*> spotLights;
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
};

class TextureData
{
public:
	~TextureData();

	GLubyte* data = nullptr;
	GLsizei width = 0;
	GLsizei height = 0;
	GLint numChannels = 0;
};

namespace SDL
{
    class ResourceManager
    {
        public:
            ResourceManager();
            virtual ~ResourceManager();

            Texture* loadTexture(const std::string&);
			TextureData* loadTextureData(const std::string&);
			std::string loadShader(const std::string&,std::map<std::string,std::string>* defineChanges = nullptr);
			Mesh* loadMesh(const std::string&);
			Scene* loadScene(const std::string&);
            
            void clearTextures();
            void deleteTexture(Texture*);
			void clearTextureDatas();
			void deleteTextureData(TextureData*);
			void clearShaders();
			void clearMeshes();
			void deleteMesh(Mesh*);
			void clearScenes();
			void deleteScene(Scene*);
            
            bool isLoaded(Texture*);
			bool isLoaded(Mesh*);
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
			std::map<std::string, Mesh*> m_meshes;
			std::map<std::string, Scene*> m_scenes;

    };
}



#endif // RESOURCEMANAGER_H
