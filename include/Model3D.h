#pragma once
#include <vector>
#include "../include/Transform3D.h"
#include <assimp/scene.h>




namespace Johnny
{
	class ResourceManager;
	class Mesh3D;
	class Shader;

	/*! \brief A class which represents a 3D model which consists of an array of Mesh3Ds
	 *
	 */
	class Model3D
	{
	public:
		/*! \brief Creates a Model3D from a aiNode
		 *  \param node The aiNode from which to get the data
		 *  \param scene The scene to which the node belongs
		 *  \param switchYandZ Defines wether to switch the y and z coordinates of the vertex positions
		 */
		Model3D(aiNode* node, const aiScene* scene, bool switchYandZ);
		Model3D();
		~Model3D();

		/*! \brief Adds a Mesh3D to the array
		 *  \param mesh The mesh to add
		 */
		void addMesh(Mesh3D* mesh);

		/*! \brief Loads the materials of the meshes
		 *  \param res The ResourceManager from which to load the materials
		 */
		void loadTextures(ResourceManager* res);
		/*! \brief Renders the model to the currently active frame buffer
		 *  \param s The Shader to which the mesh data should be loaded
		 */
		void render(Shader* s);

		/*! \return The array of meshes
		 *
		 */
		const std::vector<Mesh3D*>& getMeshes() { return m_meshes; }
		/*! \return The transform loaded from the aiNode
		 *
		 */
		const Transform3D& getTransform() const { return m_transform; }
		const std::string& getName() const { return m_name; }
	private:
		std::vector<Mesh3D*> m_meshes; //!< The array of meshes
		Transform3D m_transform;       //!< The transform loaded from the aiNode
		std::string m_name = "NONE";   //!< The name of the model
	};  
}

