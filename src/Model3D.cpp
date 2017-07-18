#include "../include/Model3D.h"
#include <assimp/scene.h>
#include "../include/Mesh3D.h"
#include "../include/Shader.h"
#include "../include/ResourceManager.h"
#include <iostream>

namespace Johnny
{
	Model3D::Model3D(aiNode* node, const aiScene* scene, bool switchZAndY)
	{
		aiVector3D scale, pos;
		aiQuaternion rot;

		node->mTransformation.Decompose(scale, rot, pos);

		m_transform.setTranslation(pos.x, pos.y, pos.z);
		m_transform.setRotation(rot.x, rot.y, rot.z);
		m_transform.setScale(scale.x, scale.y, scale.z);

		m_name = node->mName.C_Str();
		if (m_name == "")
			m_name = "NONE";

		m_meshes.reserve(node->mNumMeshes);

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			Mesh3D* meshM = new Mesh3D(scene->mMeshes[node->mMeshes[i]], scene, switchZAndY);
			m_meshes.push_back(meshM);
		}
	}

	Model3D::Model3D()
	{
		m_transform.setTranslation(0.0f, 0.0f, 0.0f);
		m_transform.setScale(1.0f, 1.0f, 1.0f);
		m_transform.setRotation(0.0f, 0.0f, 0.0f);
	}

	Model3D::~Model3D()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
			delete m_meshes[i];

		m_meshes.clear();
	}

	void Model3D::addMesh(Mesh3D* m)
	{
		m_meshes.push_back(m);
	}

	void Model3D::loadTextures(ResourceManager* res)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
			m_meshes[i]->loadMaterial(res);
	}

	void Model3D::render(Shader* s)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
			m_meshes[i]->render(s);
	}

}