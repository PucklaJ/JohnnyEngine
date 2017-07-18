#pragma once
#include "MainClass.h"

namespace Johnny
{
	class SpotLight3D;
}

class Game : public Johnny::MainClass
{
public:
	Game();
	~Game();

	bool init() override;
	bool update() override;
	bool render() override;
	void quit() override;

private:
	Johnny::SpotLight3D* m_cameraLight = nullptr;
};

