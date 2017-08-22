#include "../include/RenderManager.h"
#include "../include/Shader.h"
#include "../include/Actor.h"
#include "../include/ResourceManager.h"
#include "../include/Light3D.h"
#include "../include/OBJLoader.h"
#include "../include/MainClass.h"
#include "../include/Camera3D.h"
#include <iostream>

namespace Johnny
{
	Shader* RenderManager::DEFAULT_SHADER = nullptr;
	Shader* RenderManager::DEFAULT_SHADOWMAP_SHADER = nullptr;
	Shader* RenderManager::DEFAULT_POST_PROCESSING_SHADER = nullptr;

	void RenderManager::loadDefaultShaders(ResourceManager* res)
	{
        if(DEFAULT_POST_PROCESSING_SHADER == nullptr)
        {
            DEFAULT_POST_PROCESSING_SHADER = new Shader();

            DEFAULT_POST_PROCESSING_SHADER->addVertexShader(res->loadShader("vertexShaderFrameBuffer.glsl"));
			DEFAULT_POST_PROCESSING_SHADER->addFragmentShader(res->loadShader("fragmentShaderFrameBuffer.glsl"));

            DEFAULT_POST_PROCESSING_SHADER->addAttribute("vertexPosition", 0);
            DEFAULT_POST_PROCESSING_SHADER->addAttribute("vertexNormal", 1);
            DEFAULT_POST_PROCESSING_SHADER->addAttribute("vertexUV", 2);

            DEFAULT_POST_PROCESSING_SHADER->link();

            DEFAULT_POST_PROCESSING_SHADER->addUniform("frameBuffer");
            DEFAULT_POST_PROCESSING_SHADER->setShaderUpdater<ShaderUpdater>();
        }
	}

	void RenderManager::loadDefaultShaders3D(ResourceManager* res, Lighting3D* light)
	{
		if (DEFAULT_SHADER == nullptr)
		{
			DEFAULT_SHADER = new Shader();
			DEFAULT_SHADOWMAP_SHADER = new Shader();

			std::map<std::string, std::string> defineChanges = light->getDefineChanges();

			DEFAULT_SHADER->addVertexShader(res->loadShader("vertexShader.glsl"));
			DEFAULT_SHADER->addFragmentShader(res->loadShader("fragmentShader.glsl", &defineChanges));

			DEFAULT_SHADOWMAP_SHADER->addVertexShader(res->loadShader("vertexShaderShadowMap.glsl"));
			DEFAULT_SHADOWMAP_SHADER->addFragmentShader(res->loadShader("fragmentShaderShadowMap.glsl"));

			DEFAULT_SHADER->addAttribute("vertexPosition", 0);
			DEFAULT_SHADER->addAttribute("vertexNormal", 1);
			DEFAULT_SHADER->addAttribute("vertexUV", 2);

			DEFAULT_SHADOWMAP_SHADER->addAttribute("vertexPosition", 0);
			DEFAULT_SHADOWMAP_SHADER->addAttribute("vertexNormal", 1);
			DEFAULT_SHADOWMAP_SHADER->addAttribute("vertexUV", 2);

			DEFAULT_SHADER->link();

			DEFAULT_SHADER->addUniform("transform");
			DEFAULT_SHADER->addUniform("ambientLight");
			DEFAULT_SHADER->addUniform("worldMatrix", false);
			DEFAULT_SHADER->addUniform("eyePosition");
			Material::setUniforms(DEFAULT_SHADER);
            
            DEFAULT_SHADER->setShaderUpdater<ShaderUpdater>();

			DEFAULT_SHADOWMAP_SHADER->link();

			DEFAULT_SHADOWMAP_SHADER->addUniform("lightSpaceMatrix");
			DEFAULT_SHADOWMAP_SHADER->addUniform("worldMatrix");

			DEFAULT_SHADOWMAP_SHADER->setShadowMap(true);
            
            DEFAULT_SHADOWMAP_SHADER->setShaderUpdater<ShaderUpdater>();
		}
	}

	void RenderManager::unload()
	{
		if (DEFAULT_SHADER)
			delete DEFAULT_SHADER;
		if (DEFAULT_SHADOWMAP_SHADER)
			delete DEFAULT_SHADOWMAP_SHADER;
		if (DEFAULT_POST_PROCESSING_SHADER)
			delete DEFAULT_POST_PROCESSING_SHADER;
	}

	RenderManager::RenderManager()
	{
	}


	RenderManager::~RenderManager()
	{
	}

	void RenderManager::addShader(Shader* s)
	{
		m_shaderActors[s] = std::vector<Actor*>();
	}

	void RenderManager::addActor(Actor* a)
	{
		if (!a->getShader())
			return;

		m_shaderActors[a->getShader()].push_back(a);
	}

	void RenderManager::removeShader(Shader* s)
	{
		m_shaderActors.erase(s);
	}

	void RenderManager::removeActor(Actor* a)
	{
		if (!a->getShader())
			return;

		std::vector<Actor*>* actors = &m_shaderActors[a->getShader()];

		for (size_t i = 0; i < actors->size(); i++)
		{
			if ((*actors)[i] == a)
			{
				(*actors)[i] = actors->back();
				actors->pop_back();
				break;
			}
		}
	}

	void RenderManager::render(MainClass* m)
	{
		std::vector<Actor*>* actors = nullptr;
        Shader* shader = nullptr;
		for (std::map < Shader*, std::vector<Actor*>>::iterator it = m_shaderActors.begin(); it != m_shaderActors.end(); it++)
		{
			actors = &it->second;
			shader = it->first;
            shader->bind();
            
            shader->getShaderUpdater()->update();
            shader->getShaderUpdater()->setUniforms(m->getLighting3D());
            shader->getShaderUpdater()->setUniforms(m->getCamera3D());
            
            
			for (size_t i = 0; i < actors->size(); i++)
			{
				(*actors)[i]->setShader(it->first, false);
				(*actors)[i]->m_render_render();
			}
		}
	}

}