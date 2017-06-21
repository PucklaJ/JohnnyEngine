#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include <string>
#include <GL/glew.h>
#include <tuple>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>

class Vertex;
class Texture;
class Shader;

namespace SDL
{
	class ResourceManager;
}

class NormalPosUVIndex
{
public:
	GLuint posIndex = 0;
	GLuint normalIndex = 0;
	GLuint uvIndex = 0;
	bool createNew = false;
	std::string material = "NONE";

	bool operator<(const NormalPosUVIndex&);
	bool operator>(const NormalPosUVIndex&);
	bool operator==(const NormalPosUVIndex&);
	bool operator<=(const NormalPosUVIndex&);
	bool operator>=(const NormalPosUVIndex&);
};

extern bool operator<(const NormalPosUVIndex&,const NormalPosUVIndex&);
extern bool operator>(const NormalPosUVIndex&, const NormalPosUVIndex&);
extern bool operator==(const NormalPosUVIndex&, const NormalPosUVIndex&);
extern bool operator<=(const NormalPosUVIndex&, const NormalPosUVIndex&);
extern bool operator>=(const NormalPosUVIndex&, const NormalPosUVIndex&);

class Material
{
public:
	Material();
	Material(aiMaterial*);

	static void setUniforms(Shader*,bool withTextures = true);

	void load(const std::string&);
	void loadTextures(SDL::ResourceManager*);
	void bind(Shader*);
	void unbind();

	std::string name = "NONE";
	glm::vec3 ambientColor = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 diffuseColor = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 specularColor = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 emittedLight = glm::vec3(0.0f,0.0f,0.0f);
	GLfloat specularExponent = 1.0f;
	GLfloat transparency = 1.0f;
	glm::vec3 transmissionFilter = glm::vec3(1.0f,1.0f,1.0f);
	GLuint illumination = 0;
	std::string ambientTexture = "";
	std::string diffuseTexture = "";
	std::string specularTexture = "";

	Texture* ambientTextureT = nullptr;
	Texture* diffuseTextureT = nullptr;
	Texture* specularTextureT = nullptr;
	bool hasTextures = false;

};

class MTLLoader
{
public:
	MTLLoader(const std::string&);

	void load();
	const std::vector<Material>& getMaterials() const { return m_materials; }
private:
	std::string m_fileName = "NONE";
	std::vector<Material> m_materials;
};

class OBJLoader
{
public:
	OBJLoader(const std::string&);
	~OBJLoader();

	void load();
	void clear();

	Vertex* getVertices() { return m_vertices; }
	GLuint* getInidices() { return m_indices; }
	const std::vector<Material>& getMaterials() const { return m_materials; }

	unsigned int getVerticesSize() { return m_vertSize; }
	unsigned int getIndicesSize() { return m_indSize; }

private:
	bool findInMap(std::map<std::tuple<GLuint,GLuint,GLuint>,GLuint>&,const std::tuple<GLuint,GLuint,GLuint>&);

	std::string m_fileName = "NONE";
	Vertex* m_vertices = nullptr;
	GLuint* m_indices = nullptr;
	unsigned int m_vertSize = 0;
	unsigned int m_indSize = 0;
	std::vector<Material> m_materials;
};

#endif

