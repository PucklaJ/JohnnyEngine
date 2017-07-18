#include "../include/MainGame.h"
#include "../include/InputManager.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "../include/RenderUtil.h"
#include "../include/Mesh.h"
#include "../include/Vertex.h"
#include "../include/Shader.h"
#include "../include/ResourceManager.h"
#include <cmath>
#include <ctime>
#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Texture.h"
#include "../include/OBJLoader.h"
#include <sstream>
#include "../include/RenderBuffer.h"
#include "../include/ShadowMap.h"
#include "../include/Entity.h"
#include "../include/RenderManager.h"
#include "../include/FrameBuffer.h"
#define CENT SDL_WINDOWPOS_CENTERED

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit" << std::endl;
	getchar();
	SDL_Quit();
	exit(-1);
}

MainGame::MainGame(int w,int h) : SDL::MainClass("johnny3D-Engine",w,h)
{
	
}


MainGame::~MainGame()
{
}

bool MainGame::init()
{
	srand((unsigned int)time(nullptr));

	initLights();
	initShaders();
	initMeshes();

	m_camera->setPosition(0.0f, 3.0f, 10.0f);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

float fov = 60.0f;
static float temp = 0.0f;
static float sinTemp = 0.0f;
static bool enabled = true;
static bool enabled1 = true;

bool MainGame::update()
{
#define ROT_SPEED 40.0f
#define CAM_ROT_SPEED 0.7f
#define ZOOM_SPEED 10.0f
#define MOVE_SPEED 10.0f
#define LIGHT_MOVE_SPEED 3.0f

	if (m_inputManager->isPressed(SDLK_g))
	{
		m_mirai->getTransform().setRotation(m_mirai->getTransform().getRotation() + glm::vec3(0.0, -ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
		m_torus->getTransform().setRotation(m_torus->getTransform().getRotation() + glm::vec3(0.0, -ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
		m_saeule->getTransform().setRotation(m_saeule->getTransform().getRotation() + glm::vec3(0.0, -ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
	}
	if (m_inputManager->isPressed(SDLK_j))
	{
		m_mirai->getTransform().setRotation(m_mirai->getTransform().getRotation() + glm::vec3(0.0, ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
		m_torus->getTransform().setRotation(m_torus->getTransform().getRotation() + glm::vec3(0.0, ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
		m_saeule->getTransform().setRotation(m_saeule->getTransform().getRotation() + glm::vec3(0.0, ROT_SPEED*getDeltaTimeInSeconds(), 0.0));
	}
	if (m_inputManager->isPressed(SDLK_h))
	{
		m_mirai->getTransform().setRotation(m_mirai->getTransform().getRotation() + glm::vec3(-ROT_SPEED*getDeltaTimeInSeconds(),0.0, 0.0));
		m_torus->getTransform().setRotation(m_torus->getTransform().getRotation() + glm::vec3(-ROT_SPEED*getDeltaTimeInSeconds(), 0.0, 0.0));
		m_saeule->getTransform().setRotation(m_saeule->getTransform().getRotation() + glm::vec3(-ROT_SPEED*getDeltaTimeInSeconds(), 0.0, 0.0));
	}
	if (m_inputManager->isPressed(SDLK_z))
	{
		m_mirai->getTransform().setRotation(m_mirai->getTransform().getRotation() + glm::vec3(ROT_SPEED*getDeltaTimeInSeconds(),0.0, 0.0));
		m_torus->getTransform().setRotation(m_torus->getTransform().getRotation() + glm::vec3(ROT_SPEED*getDeltaTimeInSeconds(), 0.0, 0.0));
		m_saeule->getTransform().setRotation(m_saeule->getTransform().getRotation() + glm::vec3(ROT_SPEED*getDeltaTimeInSeconds(), 0.0, 0.0));
	}
#if NUM_POINT_LIGHTS > 0
	if (m_inputManager->isPressed(SDLK_UP))
	{
		for(unsigned int i = 0;i<NUM_POINT_LIGHTS;i++)
			pointLight[i]->position += glm::vec3(0.0f,0.0f,-1.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
	if (m_inputManager->isPressed(SDLK_DOWN))
	{
		for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
			pointLight[i]->position += glm::vec3(0.0f, 0.0f, 1.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
	if (m_inputManager->isPressed(SDLK_LEFT))
	{
		for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
			pointLight[i]->position += glm::vec3(-1.0f, 0.0f, 0.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
	if (m_inputManager->isPressed(SDLK_RIGHT))
	{
		for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
			pointLight[i]->position += glm::vec3(1.0f, 0.0f, 0.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
	if (m_inputManager->isPressed(SDLK_PAGEUP))
	{
		for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
			pointLight[i]->position += glm::vec3(0.0f, 1.0f, 0.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
	if (m_inputManager->isPressed(SDLK_PAGEDOWN))
	{
		for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
			pointLight[i]->position += glm::vec3(0.0f, -1.0f, 0.0f) * (float)(LIGHT_MOVE_SPEED*getDeltaTimeInSeconds());
	}
#endif

	if (m_inputManager->isPressed(SDLK_w))
	{
		m_camera->addPosition(0.0,0.0,-MOVE_SPEED*getDeltaTimeInSeconds(),true);
	}
	if (m_inputManager->isPressed(SDLK_s))
	{
		m_camera->addPosition(0.0, 0.0, MOVE_SPEED*getDeltaTimeInSeconds(), true);
	}
	if (m_inputManager->isPressed(SDLK_a))
	{
		m_camera->addPosition(-MOVE_SPEED*getDeltaTimeInSeconds(), 0.0, 0.0, true);
	}
	if (m_inputManager->isPressed(SDLK_d))
	{
		m_camera->addPosition(MOVE_SPEED*getDeltaTimeInSeconds(), 0.0,0.0, true);
	}
	if (m_inputManager->isPressed(SDLK_k))
	{
		m_camera->addPosition(0.0,-MOVE_SPEED*getDeltaTimeInSeconds(), 0.0, false);
	}
	if (m_inputManager->isPressed(SDLK_i))
	{
		m_camera->addPosition(0.0,MOVE_SPEED*getDeltaTimeInSeconds(), 0.0, false);
	}
#if NUM_SPOT_LIGHTS > 0
	if(enabled1)
		spotLight[0]->position = m_camera->getPosition();
#endif

	if (SDL_GetRelativeMouseMode())
	{
		m_camera->addRotation(-CAM_ROT_SPEED * (GLfloat)m_inputManager->getMouse().yrel,-CAM_ROT_SPEED * (GLfloat)m_inputManager->getMouse().xrel, CAM_ROT_SPEED * (GLfloat)m_inputManager->getMouse().wheel_y*10.0f*getDeltaTimeInSeconds());
#if NUM_SPOT_LIGHTS > 0
		if(enabled1)
			spotLight[0]->direction = m_camera->getLookDirection();
#endif
	}
		
	if (m_inputManager->justPressed(SDLK_ESCAPE))
	{
		SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE);
		SDL_WarpMouseInWindow(m_window->getWindow(),(int)(getNativeRes().x/2),(int)(getNativeRes().y/2));
	}

	

	if (m_inputManager->justPressed(SDLK_o))
	{
		if (enabled)
			glDisable(GL_MULTISAMPLE);
		else
			glEnable(GL_MULTISAMPLE);

		enabled = !enabled;
	}

	if (m_inputManager->justPressed(SDLK_p))
	{
#if NUM_SPOT_LIGHTS > 0
		/*if (enabled1)
			spotLight[0].diffuse = spotLight[0].specular = glm::vec3(0.0, 0.0, 0.0);
		else if(!enabled1)
			spotLight[0].diffuse = spotLight[0].specular = glm::vec3(1.0, 1.0, 1.0);*/
#endif
		enabled1 = !enabled1;
	}

#if NUM_POINT_LIGHTS > 0
	for(unsigned int i = 0;i<NUM_POINT_LIGHTS;i++)
		m_pointLightCube[i]->getTransform().setTranslation(pointLight[i]->position);
#endif

#if NUM_SPOT_LIGHTS > 0
	for (unsigned int i = 0; i<NUM_SPOT_LIGHTS; i++)
		m_spotLightCube[i]->getTransform().setTranslation(spotLight[i]->position);
#endif

	temp += getDeltaTimeInSeconds();
	sinTemp = sin(temp)/2.0f;

	return true;
	
}

bool MainGame::render()
{
#if NUM_SPOT_LIGHTS > 0
	if (!enabled)
	{
		RenderManager::DEFAULT_POST_PROCESSING_SHADER->bind();
		spotLight[0]->shadowMap->bind(RenderManager::DEFAULT_POST_PROCESSING_SHADER, "frameBuffer");
		getBackBufferMesh()->render(RenderManager::DEFAULT_POST_PROCESSING_SHADER);
		spotLight[0]->shadowMap->unbind();
	}
#endif

	return true;
}

void MainGame::quit()
{
	delete m_shaderWOMat;
}

void MainGame::initShaders()
{
	RenderManager::loadDefaultShaders(getResourceManager(), getLighting());

	m_shaderWOMat = new Shader();

	std::map<std::string, std::string> defineChanges = m_lighting->getDefineChanges();

	m_shaderWOMat->addVertexShader(m_resourceManager->loadShader("vertexShaderWOMaterial.glsl"));
	m_shaderWOMat->addFragmentShader(m_resourceManager->loadShader("fragmentShaderWOMaterial.glsl", &defineChanges));

	m_shaderWOMat->addAttribute("vertexPosition", 0);
	m_shaderWOMat->addAttribute("vertexNormal", 1);
	m_shaderWOMat->addAttribute("vertexUV", 2);

	m_shaderWOMat->link();

	m_shaderWOMat->addUniform("transform");
	m_shaderWOMat->addUniform("ambientLight");
	m_shaderWOMat->addUniform("worldMatrix");
	m_shaderWOMat->addUniform("eyePosition");

	m_renderManager->addShader(m_shaderWOMat);
}

void MainGame::initLights()
{
#if NUM_POINT_LIGHTS > 0
	for (unsigned int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		pointLight[i] = new PointLight();
	}
#endif
#if NUM_SPOT_LIGHTS > 0
	for (unsigned int i = 0; i < NUM_SPOT_LIGHTS; i++)
	{
		spotLight[i] = new SpotLight();
	}
#endif
#if NUM_DIRECTIONAL_LIGHTS > 0
	for (unsigned int i = 0; i < NUM_DIRECTIONAL_LIGHTS; i++)
	{
		directionalLight[i] = new DirectionalLight();
	}
#endif

	Light::ambientLight = glm::vec4(0.2, 0.2, 0.2, 1.0);
#if NUM_POINT_LIGHTS > 0
	pointLight[0]->position.y = 3.0;
	pointLight[0]->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight[0]->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight[0]->quadratic = 0.001f;
	pointLight[0]->linear = 0.1f;
	pointLight[0]->constant = 0.5f;
#if NUM_POINT_LIGHTS > 1
	pointLight[1]->position.y = 3.0f;
	pointLight[1]->position.x = 1.0f;
	pointLight[1]->position.z = -4.0f;
	pointLight[1]->diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	pointLight[1]->specular = glm::vec3(0.0f, 0.0f, 1.0f);
	pointLight[1]->quadratic = 0.001f;
	pointLight[1]->linear = 0.1f;
	pointLight[1]->constant = 1.0f;
#endif
#if NUM_POINT_LIGHTS > 2
	pointLight[2]->position.y = 3.0f;
	pointLight[2]->position.x = 3.0f;
	pointLight[2]->position.z = 3.0f;
	pointLight[2]->diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
	pointLight[2]->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight[2]->quadratic = 0.001f;
	pointLight[2]->linear = 0.1f;
	pointLight[2]->constant = 1.0f;
#endif
#if NUM_POINT_LIGHTS > 3
	pointLight[3]->position.y = 4.0f;
	pointLight[3]->position.x = -3.0f;
	pointLight[3]->position.z = 5.0f;
	pointLight[3]->diffuse = glm::vec3(0.0f, 0.0f, 1.0f);
	pointLight[3]->specular = glm::vec3(0.0f, 1.0f, 0.0f);
	pointLight[3]->quadratic = 0.001f;
	pointLight[3]->linear = 0.1f;
	pointLight[3]->constant = 3.0f;
#endif
	for (unsigned int i = 4; i < NUM_POINT_LIGHTS; i++)
	{
		pointLight[i]->position.y = (float)(rand() % 600) / 100.0f - 3.0f;
		pointLight[i]->position.x = (float)(rand() % 600) / 100.0f - 3.0f;
		pointLight[i]->position.z = (float)(rand() % 600) / 100.0f - 3.0f;
		pointLight[i]->diffuse = glm::vec3((float)(rand() % 255) / 255.0f, (float)(rand() % 255) / 255.0f, (float)(rand() % 255) / 255.0f);
		pointLight[i]->specular = glm::vec3((float)(rand() % 255) / 255.0f, (float)(rand() % 255) / 255.0f, (float)(rand() % 255) / 255.0f);
		pointLight[i]->quadratic = 0.001f;
		pointLight[i]->linear = 0.1f;
		pointLight[i]->constant = 0.6f;
	}
	for (unsigned int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		m_lighting->addLight(pointLight[i]);
	}
#endif

#if NUM_DIRECTIONAL_LIGHTS > 0
	directionalLight[0]->direction = normalize(glm::vec3(2.0f, -4.0f, 1.0f));
	directionalLight[0]->diffuse = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	directionalLight[0]->specular = glm::vec3(0.0f, 1.0f, 0.0f) * 0.0f;
	directionalLight[0]->setShadowMap(1024 * 3, 1024 * 3);
	for (unsigned int i = 0; i < NUM_DIRECTIONAL_LIGHTS; i++)
	{
		m_lighting->addLight(directionalLight[i]);
	}
#endif

#if NUM_SPOT_LIGHTS > 0
	spotLight[0]->position.x = 0.0f;
	spotLight[0]->position.z = 0.0f;
	spotLight[0]->position.y = 3.0f;
	spotLight[0]->direction.y = -1.0f;
	spotLight[0]->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	spotLight[0]->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	spotLight[0]->innerCutOff = 5.0f;
	spotLight[0]->outerCutOff = 10.0f;
	spotLight[0]->quadratic = 0.001f;
	spotLight[0]->linear = 0.1f;
	spotLight[0]->constant = 0.5f;
	spotLight[0]->setShadowMap(1024 * 3, 1024 * 3);
	for (unsigned int i = 0; i < NUM_SPOT_LIGHTS; i++)
	{
		m_lighting->addLight(spotLight[i]);
	}
#endif
}

void MainGame::initMeshes()
{
	Scene* scene = m_resourceManager->loadScene("mirai.obj");
	scene->addAsEntities(this);

	MTLLoader mtlLoader("res/materials/plane.mtl");
	mtlLoader.load();
	Material mat = mtlLoader.getMaterials()[0];
	mat.loadTextures(m_resourceManager);

	m_saeule = new Entity("saeule.obj");
	m_mirai = new Entity("mirai.obj");
	m_mirai->setShader(m_shaderWOMat);
	m_torus = new Entity("torus.obj");
	m_torus->setShader(m_shaderWOMat);
#if NUM_POINT_LIGHTS > 0
	for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
		m_pointLightCube[i] = new Entity("cubeUV.obj");
#endif
#if NUM_SPOT_LIGHTS > 0
	for (unsigned int i = 0; i<NUM_SPOT_LIGHTS; i++)
		m_spotLightCube[i] = new Entity("cubeUV.obj");
#endif
	m_plane = new Entity(createPlane(10.0f, &mat));

	Transform::setProjection(60.0f, getNativeRes().x, getNativeRes().y, 0.7f, 100.0f);

	m_mirai->getTransform().setTranslation(-1.0, 1.0, 4.0);

	m_torus->getTransform().setTranslation(0.0, 0.5, 1.0);

	m_saeule->getTransform().setTranslation(0.0, 0.0, 0.0);

	m_plane->getTransform().setTranslation(0.0, -3.0, 0.0);
#if NUM_POINT_LIGHTS > 0
	for (unsigned int i = 0; i<NUM_POINT_LIGHTS; i++)
		m_pointLightCube[i]->getTransform().setScale(0.1f, 0.1f, 0.1f);
#endif
#if NUM_SPOT_LIGHTS > 0
	for (unsigned int i = 0; i<NUM_SPOT_LIGHTS; i++)
		m_spotLightCube[i]->getTransform().setScale(0.1f, 0.1f, 0.1f);
#endif

	addChild(m_saeule);
	addChild(m_mirai);
	addChild(m_torus);
	addChild(m_plane);
#if NUM_POINT_LIGHTS > 0
	for (unsigned int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		addChild(m_pointLightCube[i]);
		m_pointLightCube[i]->setShader(m_shaderWOMat);
	}
		
#endif
#if NUM_SPOT_LIGHTS > 0
	for (unsigned int i = 0; i < NUM_SPOT_LIGHTS; i++)
	{
		addChild(m_spotLightCube[i]);
		m_spotLightCube[i]->setShader(m_shaderWOMat);
	}
		
#endif
}

Mesh * MainGame::createPlane(float size,const Material* mat)
{
	Mesh* mesh = new Mesh();

	Vertex vert[4];

	vert[0].pos = (glm::vec3(-size/2.0f,0.0,size/2.0f));
	vert[0].normal = (glm::vec3(0.0,1.0,0.0));
	vert[0].uv = (glm::vec2(0.0,0.0));

	vert[1].pos = (glm::vec3(size / 2.0f, 0.0, size / 2.0f));
	vert[1].normal = (glm::vec3(0.0, 1.0, 0.0));
	vert[1].uv = (glm::vec2(1.0, 0.0));

	vert[2].pos = (glm::vec3(size / 2.0f, 0.0, -size / 2.0f));
	vert[2].normal = (glm::vec3(0.0, 1.0, 0.0));
	vert[2].uv = (glm::vec2(1.0, 1.0));

	vert[3].pos = (glm::vec3(-size / 2.0f, 0.0, -size / 2.0f));
	vert[3].normal = (glm::vec3(0.0, 1.0, 0.0));
	vert[3].uv = (glm::vec2(0.0, 1.0));

	GLuint indices[6] =
	{
		0,1,2,2,3,0
	};

	if (mat)
	{
		mesh->setMaterial(*mat);
	}
	

	mesh->addVertices(vert, 4, indices, 6);

	return mesh;
}