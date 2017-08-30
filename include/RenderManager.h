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

	/*! \brief A class which handles the rendering of the scene, the shaders and rendering of shadow maps
	 *
	 */
	class RenderManager
	{
	public:
		static Shader* DEFAULT_SHADER;				   //!< The default Shader which renders a 3D model with materials
		static Shader* DEFAULT_SHADOWMAP_SHADER;       //!< The default Shader for rendering for a ShadowMap3D
		static Shader* DEFAULT_POST_PROCESSING_SHADER; //!< The default Shader for rendering the back buffer onto the screen

		/*! \brief Loads the default Shaders for general porpuses
		 *  \param res The ResourceManager from which to load the Shaders
		 */
		static void loadDefaultShaders(ResourceManager* res);
		/*! \brief Loads the default Shaders for 3D
		 *  \param res The ResourceManager from  which to load the Shaders
		 *  \param l The Lighting3D object from to get the amount of lights
		 */
		static void loadDefaultShaders3D(ResourceManager* res, Lighting3D* l);
		/*! \brief Unloads all default Shaders
		 *
		 */
		static void unload();

		RenderManager();
		~RenderManager();

		/*! \brief Adds a Shader so that it will be used for rendering with the RenderManager
		 *  \param s The Shader to add
		 */
		void addShader(Shader* s);
		/*! \brief Adds an Actor so that it will be rendered using the RenderManager
		 *  \param a The Actor to add
		 */
		void addActor(Actor* a);
		/*! \brief Removes a Shader from the RenderManager
		 *  \param s The Shader to remove
		 */
		void removeShader(Shader* s);
		/*! \brief Removes an Actor from the RenderManager 
		 *  \param a The Actor to remove
		 */
		void removeActor(Actor* a);

		/*! \brief Renders every Actor rwith its Shader that has been added to the RenderManager
		 *	\param m The MainClass from which to pick variables
		 */
		void render(MainClass* m);
		/*! \brief Renders every Actor that is attached to a ShadowMap3D
		 *  \param s The Shader with which the Actors are rendered
		 */
        void renderSceneForShadowMap(Shader* s);

	private:
		std::map<Shader*, std::vector<Actor*>> m_shaderActors; //!< All added Shaders and Actors
	};
}
