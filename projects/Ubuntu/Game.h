#ifndef GAME_H
#define GAME_H

#include <Johnny.h>

using namespace Johnny;

class Game : public MainClass
{
public:
	Game();
	~Game();

	bool init() override;
	bool update() override;
	bool render() override;
	void quit() override;
};

#endif
