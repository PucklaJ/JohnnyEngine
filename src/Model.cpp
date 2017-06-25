#include <Model.h>
#include <assimp/scene.h>
#include <Mesh.h>
#include <Shader.h>
#include <ResourceManager.h>
#include <iostream>

Model::Model(aiNode* node,const aiScene* scene,bool switchZAndY)
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
		Mesh* meshM = new Mesh(scene->mMeshes[node->mMeshes[i]],scene,switchZAndY);
		m_meshes.push_back(meshM);
	}
}

Model::Model()
{
	m_transform.setTranslation(0.0f, 0.0f, 0.0f);
	m_transform.setScale(1.0f, 1.0f, 1.0f);
	m_transform.setRotation(0.0f, 0.0f, 0.0f);
}

Model::~Model()
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];

	m_meshes.clear();
}

void Model::addMesh(Mesh* m)
{
	m_meshes.push_back(m);
}

void Model::loadTextures(SDL::ResourceManager* res)
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->loadMaterial(res);
}

void Model::render(Shader* s)
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->render(s);
}
