#pragma once
#include <vector>
#include <map>

class Shader;
class Lighting;

namespace SDL
{
	class Actor;
	class ResourceManager;
	class MainClass;
}

class RenderManager
{
public:
	static Shader* DEFAULT_SHADER;
	static Shader* DEFAULT_SHADOWMAP_SHADER;
	static Shader* DEFAULT_POST_PROCESSING_SHADER;

	static void loadDefaultShaders(SDL::ResourceManager*,Lighting*);
	static void unload();

	RenderManager();
	~RenderManager();

	void addShader(Shader*);
	void addActor(SDL::Actor*);
	void removeShader(Shader*);
	void removeActor(SDL::Actor*);

	void render(SDL::MainClass*);

private:
	std::map<Shader*, std::vector<SDL::Actor*>> m_shaderActors;
};

