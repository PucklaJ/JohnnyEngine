\mainpage
# JohnnyEngine

This is a 3D/2D game engine which uses SDL (GLFW) (maybe will add other frameworks) and OpenGL.

## Features

+ **Render 3D Models**
  - Materials with textures
+ **Loading 3D Models**
  - Fileformats: .obj, .dae, .fbx, .stl, .blend ...
+ **Render 2D textures**
+ **Render 2D text**
+ **3D Camera**
  - Translating
  - Rotating
+ **2D Camera**
  - Translating
  - Rotating
  - Zooming
+ **Skybox**
+ **Lighting**
  - Pointlights
  - Spotlights
  - Directionallights
+ **Shadows**
  - for Directionallights, Spotlights
+ **Gamepad input**
  - Complete simple to use gamepad implemantation
+ **Physics2D**
  - Easily accessable 2D physics implementation using [Box2D](https://box2d.org)
+ **TiledMap**
  - Loading of .tmx files of [Tiled](http://www.mapeditor.org/) using the [TMXParser](https://github.com/sainteos/tmxparser)

## Setup

### Dependencies

- [SDL2](http://www.libsdl.org)
- [GLFW](http://www.glfw.org)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
  - [freetype](https://www.freetype.org)
- [assimp](http://assimp.org/)
- [OpenGL](https://www.opengl.org/)
- [GLEW](http://glew.sourceforge.net/)
- [stb_image](https://github.com/nothings/stb) (Already included)
- [TMXParser](https://github.com/sainteos/tmxparser) (Already included)
  - [tinyxml2](http://www.grinninglizard.com/tinyxml2/)
  - [zlib](https://zlib.net)
- [Box2D](http://box2d.org/)

#### Windows - Visual Studio

1. Open the project from the projects/Windows folder

#### Linux (Ubuntu) - Code Lite

1. Download the dependencies through the download_deps.sh script
2. Open the workspace from the projects/Ubuntu folder

## Documentation

[Here](https://pucklamotzer09.github.io/JohnnyEngine/docs/html/index.html) you can find a doxygen generated documentation <br>
[Here](https://pucklamotzer09.github.io/JohnnyEngine/docs/html/md_docfiles__tutorial.html) you can find a tutorial which explains the engine

## Future Plans

+ **Water**
+ **Sceletal Animation**
+ **Point Shadows**
+ **Add a GUI Library**
+ **Physics3D with [Bullet](http://bulletphysics.org/wordpress/)**
    
