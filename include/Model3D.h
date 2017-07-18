#pragma once
#include <vector>
#include "Transform3D.h"
#include <assimp/scene.h>




namespace Johnny
{
	class ResourceManager;
	class Mesh3D;
	class Shader;

	class Model3D
	{
	public:
		Model3D(aiNode*, const aiScene*, bool);
		Model3D();
		~Model3D();

		void addMesh(Mesh3D*);

		void loadTextures(ResourceManager*);
		void render(Shader*);

		const std::vector<Mesh3D*>& getMeshes() { return m_meshes; }
		const Transform3D& getTransform() const { return m_transform; }
		const std::string& getName() const { return m_name; }
	private:
		std::vector<Mesh3D*> m_meshes;
		Transform3D m_transform;
		std::string m_name = "NONE";
	};
}

