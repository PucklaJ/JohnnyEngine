## Tutorial

To start to make games with JohnnyEngine you have to do everything according to the setup.
Then you can use the JohnnyEngine-Template to use it for your projects or create an own project.
To do so you have to create a class wich overrides Johnny::MainClass and in it you have to override
the methods init, update, render and quit. The template has done this for you in the Game.h and
Game.cpp files.

Here you can see their contents:

~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
// Game.h

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

~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
// Game.cpp

#include "Game.h"

Game::Game() : MainClass()
{
}

Game::~Game()
{
}

bool Game::init()
{
	return true;
}

bool Game::update()
{
	return true;
}

bool Game::render()
{
	return true;
}

void Game::quit()
{
}

~~~~~~~~~~~~~~~~~~~~~~~

You also need a folder called res and in it you need a folder called shaders. In it you drop all .glsl files. Then you might need the folders textures, fonts or models. In them you drop either
the texture files, font files or 3D model files.

### Actor

Every object in the game is of a class which derives from Actor. An Actor is a simple game object which basically just consists of the methods
init, update, render and quit. Init gets called when the Actor gets initialised. Update gets called every frame and updates the game logic.
Render gets called every frame after update and it renders the object. And finally quit gets called when the object gets destroyed and thrown out
of the game.
Every other class such as the Sprite2D just overrides these methods and transforms into a new game object. Using this system you can create your own
game object pretty easily with just overriding these four methods.
Every Actor also has children. These children are Actors themselves and so the game consists of just Actors which are children of other Actors.

### Getting started with some code

I will show you how you can render a Sprite.

First we have to add the InitFlags to the MainClass:
~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}

Game::Game() : MainClass(InitFlags::INIT_2D)

~~~~~~~~~~~~~~~~~~~~~~~~
There are much more InitFlags with which you determine which part of the engine should be initialised.
In the init method we have to add these lines:
~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}

Johnny::Sprite2D* spr = new Sprite2D("example.png");
addChild(spr);

~~~~~~~~~~~~~~~~~~~~~~~~
Here a new Sprite gets created with the texture example.png (It gets loaded from the folder res/textures, You can put in whatever texture you like) and then added to the MainClass
with a call to addChild(). So "spr" is a child of Game and with it the four methods init, update, render and quit get called automatically.
Now if you compile this you should see a picture in the top-left corner.

To further improve your knowledge read the documentation.