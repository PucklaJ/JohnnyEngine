#pragma once
#include <vector>
#include "Transform.h"
#include <assimp/scene.h>


class Mesh;
class Shader;

namespace SDL
{
	class ResourceManager;
}

class Model
{
public:
	Model(aiNode*,const aiScene*,bool);
	Model();
	~Model();

	void addMesh(Mesh*);

	void loadTextures(SDL::ResourceManager*);
	void render(Shader*);

	const std::vector<Mesh*>& getMeshes() { return m_meshes; }
	const Transform& getTransform() const { return m_transform; }
	const std::string& getName() const { return m_name; }
private:
	std::vector<Mesh*> m_meshes;
	Transform m_transform;
	std::string m_name = "NONE";
};

