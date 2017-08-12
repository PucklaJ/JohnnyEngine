#pragma once
#include <vector>
#include <map>



namespace Johnny
{
	class Actor;
	class ResourceManager;
	class MainClass;
	class Shader;
	class Lighting3D;

	class RenderManager
	{
	public:
		static Shader* DEFAULT_SHADER;
		static Shader* DEFAULT_SHADOWMAP_SHADER;
		static Shader* DEFAULT_POST_PROCESSING_SHADER;

		static void loadDefaultShaders(ResourceManager*);
		static void loadDefaultShaders3D(ResourceManager*, Lighting3D*);
		static void unload();

		RenderManager();
		~RenderManager();

		void addShader(Shader*);
		void addActor(Actor*);
		void removeShader(Shader*);
		void removeActor(Actor*);

		void render(MainClass*);

	private:
		std::map<Shader*, std::vector<Actor*>> m_shaderActors;
	};
}
