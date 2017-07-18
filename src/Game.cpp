#include "../include/Game.h"
#include "../include/DebugMovement3D.h"
#include "../include/RenderManager.h"
#include "../include/Light3D.h"
#include "../include/Entity3D.h"
#include "../include/ResourceManager.h"
#include "../include/Camera3D.h"
#include <iostream>
#include "../include/Skybox.h"
#include "../include/ShadowMap3D.h"
#include <TTF/SDL_ttf.h>
#include "../include/Mesh3D.h"
#include "../include/Model3D.h"
#include "../include/TextActor2D.h"
#include "../include/operators.h"
#include "../include/Timer.h"
#include "../include/mathematics.h"
#include "../include/operators.h"

Game::Game() : Johnny::MainClass(Johnny::InitFlags::INIT_3D,"johnny3D-Engine",1280,720,SDL_WINDOW_RESIZABLE)
{
}

Game::~Game()
{
}

Johnny::TextActor2D* fpsText = nullptr;

bool Game::init()
{
	Johnny::Scene* scene = m_resourceManager->loadScene("Kratos.obj");

	Johnny::SpotLight3D* light = new Johnny::SpotLight3D();
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

	m_cameraLight = new Johnny::SpotLight3D();
	m_cameraLight->position = glm::vec3(0.0, 1.0, 5.0);
	m_cameraLight->outerCutOff = 30.0f;
	m_cameraLight->innerCutOff = 28.0f;
	m_cameraLight->direction = glm::vec3(0.0, 0.0, -1.0);
	m_cameraLight->diffuse = glm::vec3(1.0, 1.0, 1.0);
	m_cameraLight->specular = glm::vec3(1.0, 1.0, 1.0);
	m_cameraLight->constant = 0.01f;
	m_cameraLight->linear = 0.01f;
	m_cameraLight->quadratic = 0.1f;

	m_lighting3D->addLight(light);
	m_lighting3D->addLight(m_cameraLight);
	Johnny::Lighting3D::ambientLight = glm::vec4(0.1,0.1,0.1,1.0);

	
	m_skybox->setTexture(Johnny::RIGHT, "right.png");
	m_skybox->setTexture(Johnny::LEFT, "left.png");
	m_skybox->setTexture(Johnny::TOP, "top.png");
	m_skybox->setTexture(Johnny::BOTTOM, "bottom.png");
	m_skybox->setTexture(Johnny::FRONT, "front.png");
	m_skybox->setTexture(Johnny::BACK, "back.png");


	Johnny::RenderManager::loadDefaultShaders(m_resourceManager, m_lighting3D);

	//scene->addAsEntities(this);

	scene->addAsEntities(this);

	Johnny::Transform3D::setProjection(70.0f, getNativeRes().x, getNativeRes().y, 0.1f, 1000.0f);

	TTF_Font* font = TTF_OpenFont("res/fonts/arial.ttf", 20);
	SDL_Color col = {255,255,255,255};

	fpsText = new Johnny::TextActor2D(font, col, std::string("FPS: ") + m_timer->getFPS());
	fpsText->getTransform().setTranslation(0.0,getNativeRes().y-30.0f);
	addChild(fpsText);

	m_timer->setMaxFPS(NO_FPS_LOCK);

	m_camera3D->setPosition(0.0f, 2.0f, 4.0f);

	addChild(new Johnny::DebugMovement3D());

	Johnny::Matrix3f mat1(1.0f), mat2(2.0f);

	GLfloat mat1Values[] =
	{
		1.0f,4.0f,7.0f,
		2.0f,5.0f,8.0f,
		3.0f,6.0f,9.0f
	};

	GLfloat mat2Values[] =
	{
		10.0f,40.0f,70.0f,
		20.0f,50.0f,80.0f,
		30.0f,60.0f,90.0f
	};

	for(int i = 0;i<9;i++)
		mat1.values[i] = mat1Values[i];

	for (int i = 0; i<9; i++)
		mat2.values[i] = mat2Values[i];

	mat1 = mat1 * mat2;

	std::cout << "MAT1:" << std::endl << mat1 << std::endl;
	std::cout << "MAT2:" << std::endl << mat2 << std::endl;

	Johnny::Vector4f v1(2,3,3,4), v2(5,6,6,9);

	v1 = v1 + v2;

	std::cout << std::string("V1: ") << v1 << std::endl;
	std::cout << std::string("V2: ") << v2 << std::endl;

	return true;
}

bool Game::update()
{
	if (m_inputManager->justPressed(Johnny::Keys::P))
	{
		if (m_cameraLight->diffuse.r == 0.0f)
			m_cameraLight->diffuse = m_cameraLight->specular = glm::vec3(1.0f, 1.0f, 1.0f);
		else
			m_cameraLight->diffuse = m_cameraLight->specular = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else if (m_inputManager->justPressed(Johnny::Keys::F))
	{
		m_window->setFullscreen(!m_window->isFullscreen());
	}
	else if (m_inputManager->justPressed(Johnny::Keys::G))
	{
		if (getNativeRes().x == 213.0f)
		{
			setNativeRes(glm::vec2(1920.0f, 1080.0f));
		}
		else
		{
			setNativeRes(glm::vec2(213.0f,120.0f));
		}

		fpsText->getTransform().setTranslation(0.0, getNativeRes().y - 30.0f);
	}

	fpsText->setText(std::string("FPS: ") + m_timer->getFPS());

	return true;
}



bool Game::render()
{
	m_cameraLight->position = m_camera3D->getPosition();
	m_cameraLight->direction = m_camera3D->getLookDirection();

	return true;
}

void Game::quit()
{
}
