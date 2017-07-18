#include "../include/ResourceManager.h"
#include <iostream>
#include "../include/MainClass.h"
#include <cstdio>
#include "../include/LogManager.h"
#include "../include/Texture.h"
#include "../include/Mesh3D.h"
#include "../include/mathematics.h"
#include "../include/stb_image.h"
#include <fstream>
#include <GL/glew.h>
#include "../include/OBJLoader.h"
#include "../include/operators.h"
#include "../include/Model3D.h"
#include "../include/Light3D.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "../include/Entity3D.h"

namespace Johnny
{
	typedef std::map<std::string, Texture*>::iterator TextureIterator;
	typedef std::map<std::string, std::string>::iterator ShaderIterator;
	typedef std::map<std::string, Mesh3D*>::iterator MeshIterator;
	typedef std::map<std::string, Scene*>::iterator SceneIterator;
	typedef std::map<std::string, TextureData*>::iterator TextureDataIterator;

	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{

	}

	std::string ResourceManager::loadShader(const std::string& fileName, std::map<std::string, std::string>* definesToChange)
	{
		ShaderIterator it;
		std::string fileContents = "";
		std::string file = getFileName(fileName);

		it = m_shaders.find(file);

		if (it != m_shaders.end())
		{
			fileContents = it->second;
		}
		else
		{
			std::ifstream fileReader("res/shaders/" + file);
			if (fileReader.fail())
			{
				LogManager::error("Couldn't load Shader: " + file);
				return "";
			}

			std::string line;

			while (std::getline(fileReader, line))
			{
				fileContents += line + "\n";
			}

			fileReader.close();

			m_shaders[file] = fileContents;
		}

		if (definesToChange)
		{
			for (std::map<std::string, std::string>::iterator it = definesToChange->begin(); it != definesToChange->end(); it++)
			{
				unsigned int pos = fileContents.find("#define " + it->first + " ");
				if (pos != std::string::npos)
				{
					unsigned int returnPos = fileContents.find("\n", pos);
					fileContents.replace(pos + ("#define " + it->first + " ").length(), returnPos - (pos + ("#define " + it->first + " ").length()), it->second);
				}
			}
		}

		return fileContents;
	}

	Mesh3D * ResourceManager::loadMesh(const std::string& fileName)
	{
		unsigned int start = SDL_GetTicks();
		std::string file = getFileName(fileName);
		LogManager::log("Loading: " + file, true, false);

		MeshIterator it;
		Mesh3D* mesh = nullptr;
		it = m_meshes.find(file);

		if (it != m_meshes.end())
		{
			mesh = it->second;
		}
		else
		{
			OBJLoader loader("res/models/" + file);

			loader.load();

			if (loader.getVertices() && loader.getInidices())
			{
				LogManager::log(std::string(" V: ") + (int)loader.getVerticesSize() + " I: " + (int)loader.getIndicesSize(), false, false);
				mesh = new Mesh3D();
				mesh->addVertices(loader.getVertices(), loader.getVerticesSize(), loader.getInidices(), loader.getIndicesSize());
				for (size_t i = 0; i < loader.getMaterials().size(); i++)
				{
					mesh->setMaterial(loader.getMaterials()[i]);
				}
				mesh->loadMaterial(this);
			}
			else
			{
				LogManager::error("\nFailed to load File Contents: " + file);
				loader.clear();
				return nullptr;
			}

			loader.clear();

			m_meshes[file] = mesh;
		}

		unsigned int end = SDL_GetTicks();

		LogManager::log(std::string(" T: ") + (int)(end - start) + " ms", false);

		return mesh;
	}

	Scene* ResourceManager::loadScene(const std::string& fileName)
	{
		Scene* scene = nullptr;
		std::string file = getFileName(fileName);

		SceneIterator it = m_scenes.find(file);
		if (it != m_scenes.end())
		{
			scene = it->second;
		}
		else
		{
			Assimp::Importer loader;
			std::string fileExtension = file.substr(file.find_last_of('.') + 1);
			bool switchZAndY = fileExtension == "blend" ? true : (fileExtension == "dae" ? true : (fileExtension == "stl" ? true : false));

			const aiScene* sceneAi = loader.ReadFile("res/models/" + file, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!sceneAi || sceneAi->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !sceneAi->mRootNode)
			{
				LogManager::error(std::string("Loading Scene: ") + loader.GetErrorString());
				return nullptr;
			}

			scene = new Scene();
			processScene(sceneAi, scene, switchZAndY);

			for (size_t i = 0; i < scene->models.size(); i++)
			{
				scene->models[i]->loadTextures(this);
			}

			m_scenes[file] = scene;
		}

		return scene;
	}

	Texture* ResourceManager::loadTexture(const std::string& fileName)
	{
		Texture* tex = nullptr;
		std::string file = getFileName(fileName);

		TextureIterator it;

		for (it = m_textures.begin(); it != m_textures.end(); it++)
		{
			if (it->first.compare(file) == 0)
			{
				break;
			}
		}

		if (it != m_textures.end())
		{
			tex = it->second;
		}
		else
		{
			GLsizei width = 0, height = 0, numChannels = 0;

			GLubyte* pixels = stbi_load(("res/textures/" + file).c_str(), &width, &height, &numChannels, 4);

			if (pixels == nullptr || numChannels == 0)
			{
				LogManager::error("Loading Texture: " + file);
				return nullptr;
			}

			Texture* tex = new Texture(pixels, width, height);

			stbi_image_free(pixels);

			m_textures[file] = tex;
		}

		return tex;
	}

	TextureData* ResourceManager::loadTextureData(const std::string& fileName)
	{
		std::string file = getFileName(fileName);

		TextureDataIterator it = m_textureBytes.find(file);
		if (it != m_textureBytes.end())
			return it->second;
		else
		{
			TextureData* data = new TextureData();
			data->data = stbi_load(("res/textures/" + file).c_str(), &data->width, &data->height, &data->numChannels, 4);

			if (data->numChannels == 0 || data->data == nullptr)
			{
				LogManager::error("Couldn't load TextureData of " + file);
				delete data;
			}
			else
			{
				m_textureBytes[file] = data;
				return data;
			}
		}

		return nullptr;
	}

	void ResourceManager::clearTextures()
	{
		for (TextureIterator it = m_textures.begin(); it != m_textures.end(); it++)
		{
			if (it->second)
				delete it->second;
		}

		m_textures.clear();
	}

	void ResourceManager::clearShaders()
	{
		m_shaders.clear();
	}

	void ResourceManager::clearMeshes()
	{
		for (MeshIterator it = m_meshes.begin(); it != m_meshes.end(); it++)
		{
			if (it->second)
				delete it->second;
		}

		m_meshes.clear();
	}

	void ResourceManager::deleteMesh(Mesh3D* m)
	{
		for (MeshIterator it = m_meshes.begin(); it != m_meshes.end(); it++)
		{
			if (it->second == m)
			{
				delete it->second;
				m_meshes.erase(it);
				break;
			}
		}
	}

	void ResourceManager::clearScenes()
	{
		for (SceneIterator it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			delete it->second;
		}

		m_scenes.clear();
	}

	void ResourceManager::deleteScene(Scene* s)
	{
		for (SceneIterator it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			if (it->second == s)
			{
				delete s;
				m_scenes.erase(it);
				break;
			}
		}
	}

	void ResourceManager::deleteTexture(Texture* tex)
	{
		for (TextureIterator it = m_textures.begin(); it != m_textures.end(); it++)
		{
			if (it->second == tex)
			{
				delete it->second;
				m_textures.erase(it);
				break;
			}
		}
	}

	void ResourceManager::clearTextureDatas()
	{
		for (TextureDataIterator it = m_textureBytes.begin(); it != m_textureBytes.end(); it++)
		{
			delete it->second;
		}

		m_textureBytes.clear();
	}

	void ResourceManager::deleteTextureData(TextureData* td)
	{
		for (TextureDataIterator it = m_textureBytes.begin(); it != m_textureBytes.end(); it++)
		{
			if (it->second == td)
			{
				delete it->second;
				m_textureBytes.erase(it);
				break;
			}
		}
	}

	bool ResourceManager::isLoaded(Mesh3D* m)
	{
		for (MeshIterator it = m_meshes.begin(); it != m_meshes.end(); it++)
		{
			if (it->second == m)
				return true;
		}

		return false;
	}

	bool ResourceManager::isLoaded(Scene* s)
	{
		for (SceneIterator it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			if (it->second == s)
			{
				return true;
			}
		}

		return false;
	}

	bool ResourceManager::isLoaded(TextureData* td)
	{
		for (TextureDataIterator it = m_textureBytes.begin(); it != m_textureBytes.end(); it++)
		{
			if (it->second == td)
			{
				return true;
			}
		}

		return false;
	}

	void ResourceManager::clear()
	{
		clearTextures();
		clearTextureDatas();
		clearShaders();
		clearMeshes();
		clearScenes();
	}

	void ResourceManager::processScene(const aiScene* sceneAi, Scene* scene, bool switchZAndY)
	{
		processNode(sceneAi->mRootNode, sceneAi, scene, switchZAndY);
	}

	void ResourceManager::processNode(aiNode* node, const aiScene* sceneAi, Scene* scene, bool switchZAndY)
	{
		if (node->mMeshes)
		{
			Model3D* model = new Model3D(node, sceneAi, switchZAndY);
			scene->models.push_back(model);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], sceneAi, scene, switchZAndY);
		}
	}

	std::string ResourceManager::getFileName(const std::string& directory)
	{
		unsigned int pos = 0;

		pos = directory.find_last_of('/');
		if (pos == std::string::npos)
			pos = directory.find_last_of('\\');

		if (pos == std::string::npos)
			return directory;
		else
		{
			return directory.substr(pos + 1);
		}
	}

	bool ResourceManager::isLoaded(Texture* tex)
	{
		for (TextureIterator it = m_textures.begin(); it != m_textures.end(); it++)
		{
			if (it->second && it->second == tex)
				return true;
		}

		return false;
	}

	void Scene::addAsEntities(MainClass* m)
	{
		if (this)
		{
			for (size_t i = 0; i < models.size(); i++)
			{
				Entity3D* ent = new Entity3D(models[i]);
				m->addChild(ent);
			}
		}
	}

	Model3D* Scene::getModel(const std::string& name)
	{
		for (size_t i = 0; i < models.size(); i++)
		{
			if (models[i]->getName() == name)
				return models[i];
		}

		return nullptr;
	}

	TextureData::~TextureData()
	{
		stbi_image_free(data);
	}

}
