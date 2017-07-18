#include "../include/Game.h"
#include <iostream>
#include <cstdio>
#include <glm\glm.hpp>
#undef main

int main(int argc, char* argv[])
{
	

	Game().run();

#ifdef _DEBUG
	std::cout << std::endl << "Enter any key to quit" << std::endl;
	getchar();
#endif

	return 0;
}