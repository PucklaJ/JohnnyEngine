#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <chrono>
#include "Transform.h"
#include "Light.h"
#include "MainClass.h"
#define DEF_W 1280
#define DEF_H 720

#define NUM_POINT_LIGHTS 0
#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_SPOT_LIGHTS 1

class Entity;
class Mesh;
class Shader;
class ShadowMap;
class Material;

class MainGame : public SDL::MainClass
{
public:
	MainGame(int width = DEF_W, int height = DEF_H);
	~MainGame();

	bool init();
	bool update();
	bool render();
	void quit();
	
private:
	void initShaders();
	void initLights();
	void initMeshes();

	Mesh* createPlane(float size = 10.0,const Material* mat = nullptr);

	Entity* m_mirai = nullptr;
	Entity* m_torus = nullptr;
	Entity* m_saeule = nullptr;
	Entity* m_plane = nullptr;
#if NUM_POINT_LIGHTS > 0
	Entity* m_pointLightCube[NUM_POINT_LIGHTS];
#endif
#if NUM_SPOT_LIGHTS > 0
	Entity* m_spotLightCube[NUM_SPOT_LIGHTS];
#endif
	Shader* m_shaderWOMat = nullptr;
#if NUM_POINT_LIGHTS > 0
	PointLight* pointLight[NUM_POINT_LIGHTS];
#endif
#if NUM_DIRECTIONAL_LIGHTS > 0
	DirectionalLight* directionalLight[NUM_DIRECTIONAL_LIGHTS];
#endif
#if NUM_SPOT_LIGHTS > 0
	SpotLight* spotLight[NUM_SPOT_LIGHTS];
#endif
};

