#include "Game.h"
#include "DebugMovement.h"
#include "RenderManager.h"
#include "Light.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Camera.h"
#include <iostream>
#include "Skybox.h"
#include "ShadowMap.h"
#include <TTF/SDL_ttf.h>
#include "Mesh.h"
#include "Model.h"
#include "TextActor.h"
#include "operators.h"

Game::Game() : SDL::MainClass("johnny3D-Engine",1280,720,SDL_WINDOW_RESIZABLE)
{
}

Game::~Game()
{
}

SDL::TextActor* fpsText = nullptr;

bool Game::init()
{
	Scene* scene = m_resourceManager->loadScene("Kratos.obj");

	SpotLight* light = new SpotLight();
	light->position = glm::vec3(0.0,1.0,5.0);
	light->outerCutOff = 60.0f;
	light->innerCutOff = 40.0f;
	light->direction = glm::vec3(0.0,0.0,-1.0);
	light->diffuse = glm::vec3(2.0,2.0,2.0);
	light->specular = glm::vec3(1.0,1.0,1.0);
	light->constant = 0.01f;
	light->linear = 0.01f;
	light->quadratic = 0.1f;
	light->setShadowMap(1024 * 3, 1024 * 3);

	m_cameraLight = new SpotLight();
	m_cameraLight->position = glm::vec3(0.0, 1.0, 5.0);
	m_cameraLight->outerCutOff = 30.0f;
	m_cameraLight->innerCutOff = 28.0f;
	m_cameraLight->direction = glm::vec3(0.0, 0.0, -1.0);
	m_cameraLight->diffuse = glm::vec3(1.0, 1.0, 1.0);
	m_cameraLight->specular = glm::vec3(1.0, 1.0, 1.0);
	m_cameraLight->constant = 0.01f;
	m_cameraLight->linear = 0.01f;
	m_cameraLight->quadratic = 0.1f;

	m_lighting->addLight(light);
	m_lighting->addLight(m_cameraLight);
	Lighting::ambientLight = glm::vec4(0.1,0.1,0.1,1.0);

	
	m_skybox->setTexture(RIGHT, "right.png");
	m_skybox->setTexture(LEFT, "left.png");
	m_skybox->setTexture(TOP, "top.png");
	m_skybox->setTexture(BOTTOM, "bottom.png");
	m_skybox->setTexture(FRONT, "front.png");
	m_skybox->setTexture(BACK, "back.png");


	RenderManager::loadDefaultShaders(m_resourceManager, m_lighting);

	//scene->addAsEntities(this);

	scene->addAsEntities(this);

	Transform::setProjection(70.0f, getNativeRes().x, getNativeRes().y, 0.1f, 1000.0f);

	TTF_Font* font = TTF_OpenFont("res/fonts/arial.ttf", 20);
	SDL_Color col = {255,255,255,255};

	fpsText = new SDL::TextActor(font, col, std::string("FPS: ") + getFPS());
	fpsText->getTransform().setTranslation(0.0,getNativeRes().y-30.0f,0.0f);
	addChild(fpsText);

	setMaxFPS(NO_FPS_LOCK);

	m_camera->setPosition(0.0f, 2.0f, 4.0f);

	addChild(new DebugMovement());

	return true;
}

bool Game::update()
{
	if (m_inputManager->justPressed(SDLK_p))
	{
		if (m_cameraLight->diffuse.r == 0.0f)
			m_cameraLight->diffuse = m_cameraLight->specular = glm::vec3(1.0f, 1.0f, 1.0f);
		else
			m_cameraLight->diffuse = m_cameraLight->specular = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else if (m_inputManager->justPressed(SDLK_f))
	{
		m_window->setFullscreen(!m_window->isFullscreen());
	}
	else if (m_inputManager->justPressed(SDLK_g))
	{
		if (getNativeRes().x == 213.0f)
		{
			setNativeRes(glm::vec2(1920.0f, 1080.0f));
		}
		else
		{
			setNativeRes(glm::vec2(213.0f,120.0f));
		}

		fpsText->getTransform().setTranslation(0.0, getNativeRes().y - 30.0f, 0.0f);
	}

	fpsText->setText(std::string("FPS: ") + getFPS());

	return true;
}



bool Game::render()
{
	m_cameraLight->position = m_camera->getPosition();
	m_cameraLight->direction = m_camera->getLookDirection();

	return true;
}

void Game::quit()
{
}
