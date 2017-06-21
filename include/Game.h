#pragma once
#include "MainClass.h"

class SpotLight;

class Game :
	public SDL::MainClass
{
public:
	Game();
	~Game();

	bool init() override;
	bool update() override;
	bool render() override;
	void quit() override;

private:
	SpotLight* m_cameraLight = nullptr;
};

