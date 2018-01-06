#define SDL_MAIN_HANDLED 1
#include "Game.h"

#ifdef _DEBUG
int main(int args,char* argv[])
#else
int SDL_main(int args, char* argv[])
#endif
{
	Game().run();

	return 0;
}