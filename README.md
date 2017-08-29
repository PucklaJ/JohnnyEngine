\mainpage
# JohnnyEngine

This is a 3D/2D game engine which uses SDL (maybe will add other frameworks) and OpenGL.

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
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [assimp](http://assimp.org/)
- [OpenGL](https://www.opengl.org/)
- [GLEW](http://glew.sourceforge.net/)
- [stb_image](https://github.com/nothings/stb) (Already included)
- [TMXParser](https://github.com/sainteos/tmxparser) (Already included)
  - [tinyxml2](http://www.grinninglizard.com/tinyxml2/)
  - [zlib](https://zlib.net)
- [Box2D](http://box2d.org/)

#### Windows - Visual Studio

1. Download dependencies from links above
2. Put the .h/.hpp and .lib files in seperate directories
3. In Visual Studio
  - link to the .h/.hpp files
  - link to the .lib files
4. Add the files of the engine to the project
5. Put .dll files to the executable directory
5. It should compile and link

#### Linux (Ubuntu) - Eclipse

1. Download the dependencies <br>
  1.1 Execute these commands <br>
 

      sudo apt-get install libsdl2    
      sudo apt-get install libsdl2-ttf    
      sudo apt-get install assimp    
      sudo apt-get install glew    
      sudo apt-get install libz    
      sudo apt-get install tinyxml2    

2. In Eclipse <br>
  2.1 Add the libraries to the project <br>
3. It should compile and link <br>

## Future Plans

+ **Water**
+ **Sceletal Animation**
+ **Point Shadows**
+ **Add a GUI Library**
+ **Physics3D with [Bullet](http://bulletphysics.org/wordpress/)**
    
