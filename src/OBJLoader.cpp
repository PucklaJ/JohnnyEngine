#include "../include/OBJLoader.h"
#include "../include/ResourceManager.h"
#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Vertex3D.h"
#include <SDL2/SDL.h>
#include <assimp/scene.h>
#include <fstream>
#include <iostream>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS
#define FIND(_pair)                                                            \
  (normalPosUVIndices.find(std::tuple<GLuint, GLuint, GLuint>(                 \
      _pair.posIndex, _pair.normalIndex, _pair.uvIndex)))
#define INSERT(_pair)                                                          \
  (normalPosUVIndices.insert(                                                  \
      std::pair<std::tuple<GLuint, GLuint, GLuint>, GLuint>(                   \
          std::tuple<GLuint, GLuint, GLuint>(                                  \
              _pair.posIndex, _pair.normalIndex, _pair.uvIndex),               \
          curIndex++)))
#define GET(_pair)                                                             \
  (normalPosUVIndices[std::tuple<GLuint, GLuint, GLuint>(                      \
      _pair.posIndex, _pair.normalIndex, _pair.uvIndex)])

namespace Johnny {
OBJLoader::OBJLoader(const std::string &file) : m_fileName(file) {}

OBJLoader::~OBJLoader() {}

const Material *getMaterial(const std::string &name,
                            const std::vector<Material> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i].name == name)
      return &vec[i];
  }

  return nullptr;
}

void OBJLoader::load() {
  std::ifstream fileReader(m_fileName);
  if (fileReader.fail()) {
    std::cout << " Failed to open Mesh: " << m_fileName << std::endl;
    return;
  }

  std::string fileContents = "";
  std::string line = "";
  std::string curToken = "";

  std::vector<Vertex3D> vertices;
  std::vector<GLuint> indices;

  std::map<std::tuple<GLuint, GLuint, GLuint>, GLuint> normalPosUVIndices;
  std::vector<NormalPosUVIndex> normalPosUVIndicesAll;
  std::vector<Vector3f> positions;
  std::vector<Vector3f> normals;
  std::vector<Vector2f> uvs;
  std::vector<std::string> tokens;
  std::vector<std::string> materialFilesToLoad;
  std::vector<Material> materials;
  std::string curMaterial = "NONE";

  GLuint curIndex = 0;

  size_t n1;
  size_t n2;
  size_t n3;
  NormalPosUVIndex pair[3];

  while (std::getline(fileReader, line)) {
    fileContents += line + "\n";
  }

  for (size_t i = 0; i < fileContents.length(); i++) {
    if (fileContents[i] == '\n') {
      tokens.push_back(curToken);

      /*if (tokens[0] == "#")
              continue;
      else */
      if (tokens[0] == "mtllib") {
        materialFilesToLoad.push_back(tokens[1]);
      }
      /*else if (tokens[0] == "o")
              continue;*/
      else if (tokens[0] == "v") {
        positions.push_back(Vector3f(atof(tokens[1].c_str()),
                                     atof(tokens[2].c_str()),
                                     atof(tokens[3].c_str())));
      } else if (tokens[0] == "vt") {
        uvs.push_back(
            Vector2f(atof(tokens[1].c_str()), atof(tokens[2].c_str())));
      } else if (tokens[0] == "vn") {
        normals.push_back(Vector3f(atof(tokens[1].c_str()),
                                   atof(tokens[2].c_str()),
                                   atof(tokens[3].c_str())));
      } else if (tokens[0] == "usemtl")
        curMaterial = tokens[1];
      /*else if (tokens[0] == "s")
              continue;*/
      else if (tokens[0] == "f") {
        n1 = tokens[1].find("//", 0);
        if (n1 == std::string::npos) {
          n1 = tokens[1].find('/', 0);
          if (n1 == std::string::npos) {
            pair[0].posIndex = atoi(tokens[1].c_str()) - 1;
            pair[1].posIndex = atoi(tokens[2].c_str()) - 1;
            pair[2].posIndex = atoi(tokens[3].c_str()) - 1;
          } else {
            pair[0].posIndex = atoi(tokens[1].substr(0, n1).c_str()) - 1;
            pair[1].posIndex =
                atoi(tokens[2].substr(0, tokens[2].find('/', 0)).c_str()) - 1;
            pair[2].posIndex =
                atoi(tokens[3].substr(0, tokens[3].find('/', 0)).c_str()) - 1;

            n2 = tokens[1].find('/', n1 + 1);
            pair[0].uvIndex =
                atoi(tokens[1].substr(n1 + 1, n2 - n1 - 1).c_str()) - 1;
            n2 = tokens[2].find('/', 0);
            n3 = tokens[2].find('/', n2 + 1);
            pair[1].uvIndex =
                atoi(tokens[2].substr(n2 + 1, n3 - n2 - 1).c_str()) - 1;
            n2 = tokens[3].find('/', 0);
            n3 = tokens[3].find('/', n2 + 1);
            pair[2].uvIndex =
                atoi(tokens[3].substr(n2 + 1, n3 - n2 - 1).c_str()) - 1;

            pair[0].normalIndex =
                atoi(
                    tokens[1].substr(tokens[1].find_last_of('/') + 1).c_str()) -
                1;
            pair[1].normalIndex =
                atoi(
                    tokens[2].substr(tokens[2].find_last_of('/') + 1).c_str()) -
                1;
            pair[2].normalIndex = atoi(tokens[3].substr(n3 + 1).c_str()) - 1;
          }
        } else {
          n2 = tokens[2].find('/', 0);
          n3 = tokens[3].find('/', 0);

          pair[0].posIndex = atoi(tokens[1].substr(0, n1).c_str()) - 1;
          pair[1].posIndex = atoi(tokens[2].substr(0, n2).c_str()) - 1;
          pair[2].posIndex = atoi(tokens[3].substr(0, n3).c_str()) - 1;

          pair[0].normalIndex = atoi(tokens[1].substr(n1 + 2).c_str()) - 1;
          pair[1].normalIndex = atoi(tokens[2].substr(n2 + 2).c_str()) - 1;
          pair[2].normalIndex = atoi(tokens[3].substr(n3 + 2).c_str()) - 1;
        }

        pair[0].material = curMaterial;
        pair[1].material = curMaterial;
        pair[2].material = curMaterial;

        if (FIND(pair[0]) == normalPosUVIndices.end()) {
          INSERT(pair[0]);

          pair[0].createNew = true;
        } else {
          pair[0].createNew = false;
        }

        if (FIND(pair[1]) == normalPosUVIndices.end()) {
          INSERT(pair[1]);
          pair[1].createNew = true;
        } else {
          pair[1].createNew = false;
        }

        if (FIND(pair[2]) == normalPosUVIndices.end()) {
          INSERT(pair[2]);
          pair[2].createNew = true;
        } else {
          pair[2].createNew = false;
        }

        normalPosUVIndicesAll.push_back(pair[0]);
        normalPosUVIndicesAll.push_back(pair[1]);
        normalPosUVIndicesAll.push_back(pair[2]);
      }

      tokens.clear();
      curToken = "";
    } else if (fileContents[i] == ' ') {
      tokens.push_back(curToken);
      curToken = "";
    } else {
      curToken += fileContents[i];
    }
  }

  for (size_t i = 0; i < materialFilesToLoad.size(); i++) {
    MTLLoader loader("res/materials/" + materialFilesToLoad[i]);
    loader.load();

    for (size_t j = 0; j < loader.getMaterials().size(); j++) {
      materials.push_back(loader.getMaterials()[j]);
    }
  }

  vertices.reserve(positions.size());
  indices.reserve(normalPosUVIndicesAll.size());

  Material lastMaterial;
  lastMaterial.name = "NONE";
  Material material;

  for (size_t i = 0; i < normalPosUVIndicesAll.size(); i++) {
    GLuint index = GET(normalPosUVIndicesAll[i]);
    if (i % 10 == 0)

      if (normalPosUVIndicesAll[i].material != "NONE" &&
          (lastMaterial.name == "NONE" ||
           lastMaterial.name != normalPosUVIndicesAll[i].material)) {
        const Material *pointer =
            getMaterial(normalPosUVIndicesAll[i].material, materials);
        if (pointer)
          lastMaterial = *pointer;
        else
          lastMaterial.name = "NONE";
        if (lastMaterial.name != "NONE")
          material = lastMaterial;
        else
          material.name = "NONE";

        if (material.name != "NONE")
          m_materials.push_back(material);
      }

    if (normalPosUVIndicesAll[i].createNew) {
      Vertex3D vert;

      vert.pos = (positions[normalPosUVIndicesAll[i].posIndex]);
      if (!normals.empty())
        vert.normal = (normals[normalPosUVIndicesAll[i].normalIndex]);
      if (!uvs.empty())
        vert.uv = (uvs[normalPosUVIndicesAll[i].uvIndex]);

      vertices.push_back(vert);
    }

    indices.push_back(index);
  }

  if (material.name != "NONE") {
    m_materials.push_back(material);
  }

  m_vertices = new Vertex3D[vertices.size()];
  m_indices = new GLuint[indices.size()];

  m_vertSize = (unsigned int)vertices.size();
  m_indSize = (unsigned int)indices.size();

  for (size_t i = 0; i < vertices.size(); i++) {
    m_vertices[i] = vertices[i];
  }

  for (size_t i = 0; i < indices.size(); i++) {
    m_indices[i] = indices[i];
  }
}

void OBJLoader::clear() {
  if (m_vertices)
    delete[] m_vertices;
  if (m_indices)
    delete[] m_indices;
}

bool OBJLoader::findInMap(
    std::map<std::tuple<GLuint, GLuint, GLuint>, GLuint> &_map,
    const std::tuple<GLuint, GLuint, GLuint> &key) {
  for (std::map<std::tuple<GLuint, GLuint, GLuint>, GLuint>::iterator it =
           _map.begin();
       it != _map.end(); it++) {
    if (std::get<0>(it->first) == std::get<0>(key) &&
        std::get<1>(it->first) == std::get<1>(key) &&
        std::get<2>(it->first) == std::get<2>(key)) {
      return true;
    }
  }

  return false;
}

bool NormalPosUVIndex::operator==(const NormalPosUVIndex &n) {
  return this->posIndex == n.posIndex && this->normalIndex == n.normalIndex;
}

bool NormalPosUVIndex::operator<=(const NormalPosUVIndex &n) {
  return !((*this) > n);
}

bool NormalPosUVIndex::operator>=(const NormalPosUVIndex &n) {
  return !((*this) < n);
}

bool NormalPosUVIndex::operator<(const NormalPosUVIndex &n) {
  return this->posIndex + this->normalIndex < n.posIndex + n.normalIndex;
}

bool NormalPosUVIndex::operator>(const NormalPosUVIndex &n) {
  return this->posIndex + this->normalIndex > n.posIndex + n.normalIndex;
}

bool operator<(const NormalPosUVIndex &n1, const NormalPosUVIndex &n2) {
  return n1.posIndex + n1.normalIndex < n2.posIndex + n2.normalIndex;
}

bool operator>(const NormalPosUVIndex &n1, const NormalPosUVIndex &n2) {
  return n1.posIndex + n1.normalIndex > n2.posIndex + n2.normalIndex;
}

bool operator==(const NormalPosUVIndex &n1, const NormalPosUVIndex &n2) {
  return n1.posIndex == n2.posIndex && n1.normalIndex == n2.normalIndex;
}

bool operator<=(const NormalPosUVIndex &n1, const NormalPosUVIndex &n2) {
  return !(n1 > n2);
}

bool operator>=(const NormalPosUVIndex &n1, const NormalPosUVIndex &n2) {
  return !(n1 < n2);
}

MTLLoader::MTLLoader(const std::string &fileName) : m_fileName(fileName) {}

void MTLLoader::load() {
  std::ifstream fileReader(m_fileName);
  if (fileReader.fail()) {
    std::cerr << std::endl
              << "Failed to open MaterialFile: " << m_fileName << std::endl;
    return;
  }

  std::string fileContents = "";
  std::string line = "";
  std::string curToken = "";
  std::string curMaterialContents = "";
  std::vector<std::string> materialFileContents;
  bool readingMaterial = false;

  while (std::getline(fileReader, line)) {
    fileContents += line + '\n';
  }

  for (size_t i = 0; i < fileContents.length(); i++) {
    if (fileContents[i] == '\n') {
      curToken = "";
    } else {
      if (fileContents[i] == ' ') {
        if (curToken == "newmtl") {
          if (readingMaterial) {
            materialFileContents.push_back(curMaterialContents.substr(
                0, curMaterialContents.length() - curToken.length()));
          }

          readingMaterial = true;
          curMaterialContents = curToken;
        }
      } else {
        curToken += fileContents[i];
      }
    }

    if (readingMaterial) {
      curMaterialContents += fileContents[i];
    }
  }

  materialFileContents.push_back(curMaterialContents);

  for (size_t i = 0; i < materialFileContents.size(); i++) {
    Material mat;
    mat.load(materialFileContents[i]);
    m_materials.push_back(mat);
  }
}

Material::Material()
    : name("NONE"), ambientColor(1.0f, 1.0f, 1.0f),
      diffuseColor(1.0f, 1.0f, 1.0f), specularColor(1.0f, 1.0f, 1.0f),
      emittedLight(0.0f, 0.0f, 0.0f), specularExponent(1.0f),
      transparency(1.0f), transmissionFilter(1.0f, 1.0f, 1.0f), illumination(0),
      ambientTexture(""), diffuseTexture(""), specularTexture(""),
      ambientTextureT(nullptr), diffuseTextureT(nullptr),
      specularTextureT(nullptr) {}

Material::Material(aiMaterial *material) : Material() {
  aiString str;
  aiColor3D color;
  material->Get(AI_MATKEY_NAME, str);
  name = str.C_Str();
  if (name != "DefaultMaterial") {
    str = "";
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    ambientColor = Colorf(color.r, color.g, color.b);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    diffuseColor = Colorf(color.r, color.g, color.b);
    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    specularColor = Colorf(color.r, color.g, color.b);
    material->Get(AI_MATKEY_SHININESS, specularExponent);
    material->Get(AI_MATKEY_OPACITY, transparency);
    material->GetTexture(aiTextureType_AMBIENT, 0, &str);
    ambientTexture = str.C_Str();
    material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
    diffuseTexture = str.C_Str();
    material->GetTexture(aiTextureType_SPECULAR, 0, &str);
    specularTexture = str.C_Str();
  } else {
    name = "NONE";
  }
}

void Material::setUniforms(Shader *s, bool withTextures) {
  s->addUniform("material.ambientColor");
  s->addUniform("material.diffuseColor", false);
  s->addUniform("material.specularColor", false);
  s->addUniform("material.transperancy");
  s->addUniform("material.specularExponent", false);
  // s->addUniform("material.emittedLight");
  s->addUniform("material.transmissionFilter");
  if (withTextures) {
    s->addUniform("material.ambientTexture");
    s->addUniform("material.diffuseTexture");
    s->addUniform("material.specularTexture");
    s->addUniform("material.hasTextures");
  }
}

void Material::load(const std::string &contents) {
  std::string curToken = "";
  std::vector<std::string> tokens;

  for (size_t i = 0; i < contents.length(); i++) {
    if (contents[i] == '\n') {
      tokens.push_back(curToken);
      curToken = "";

      if (tokens[0] == "newmtl") {
        name = tokens[1];
      } else if (tokens[0] == "Ns") {
        specularExponent = (GLfloat)atof(tokens[1].c_str());
      } else if (tokens[0] == "Ka") {
        if (tokens.size() == 2) {
          ambientColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[1].c_str()),
                     atof(tokens[1].c_str()));
        } else if (tokens.size() == 3) {
          ambientColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[2].c_str()));
        } else {
          ambientColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[3].c_str()));
        }

      } else if (tokens[0] == "Kd") {
        if (tokens.size() == 2) {
          diffuseColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[1].c_str()),
                     atof(tokens[1].c_str()));
        } else if (tokens.size() == 3) {
          diffuseColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[2].c_str()));
        } else {
          diffuseColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[3].c_str()));
        }
      } else if (tokens[0] == "Ks") {
        if (tokens.size() == 2) {
          specularColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[1].c_str()),
                     atof(tokens[1].c_str()));
        } else if (tokens.size() == 3) {
          specularColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[2].c_str()));
        } else {
          specularColor =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[3].c_str()));
        }

      } else if (tokens[0] == "Ke") {
        if (tokens.size() == 2) {
          emittedLight =
              Colorf(atof(tokens[1].c_str()), atof(tokens[1].c_str()),
                     atof(tokens[1].c_str()));
        } else if (tokens.size() == 3) {
          emittedLight =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[2].c_str()));
        } else {
          emittedLight =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[3].c_str()));
        }
      } else if (tokens[0] == "Tf") {
        if (tokens.size() == 2) {
          transmissionFilter =
              Colorf(atof(tokens[1].c_str()), atof(tokens[1].c_str()),
                     atof(tokens[1].c_str()));
        } else if (tokens.size() == 3) {
          transmissionFilter =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[2].c_str()));
        } else {
          transmissionFilter =
              Colorf(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
                     atof(tokens[3].c_str()));
        }
      } else if (tokens[0] == "illum") {
        illumination = atoi(tokens[1].c_str());
      } else if (tokens[0] == "d") {
        transparency = (GLfloat)atof(tokens[1].c_str());
      } else if (tokens[0] == "map_Kd") {
        diffuseTexture = tokens[1];
      } else if (tokens[0] == "map_Ka") {
        ambientTexture = tokens[1];
      } else if (tokens[0] == "map_Ks") {
        specularTexture = tokens[1];
      }

      tokens.clear();
    } else {
      if (contents[i] == ' ') {
        tokens.push_back(curToken);
        curToken = "";
      } else {
        curToken += contents[i];
      }
    }
  }
}

void Material::loadTextures(ResourceManager *res) {
  if (ambientTexture != "") {
    ambientTextureT = res->loadTexture(ambientTexture);
  }
  if (diffuseTexture != "") {
    diffuseTextureT = res->loadTexture(diffuseTexture);
    if (ambientTextureT == nullptr)
      ambientTextureT = diffuseTextureT;
  }
  if (specularTexture != "") {
    specularTextureT = res->loadTexture(specularTexture);
    if (diffuseTextureT == nullptr)
      diffuseTextureT = specularTextureT;
    if (ambientTextureT == nullptr)
      ambientTextureT = specularTextureT;
  }

  if (ambientTextureT || diffuseTextureT || specularTextureT)
    hasTextures = true;
}

void Material::bind(Shader *s) {
  s->setUniform("material.ambientColor", ambientColor);
  s->setUniform("material.diffuseColor", diffuseColor);
  s->setUniform("material.specularColor", specularColor);
  s->setUniform("material.transperancy", transparency);
  s->setUniform("material.specularExponent", specularExponent);
  s->setUniform("material.emittedLight", emittedLight);
  s->setUniform("material.transmissionFilter", transmissionFilter);
  s->setUniform("material.hasTextures", hasTextures);

  if (ambientTextureT)
    ambientTextureT->bind(s, "material.ambientTexture", 0);
  if (diffuseTextureT)
    diffuseTextureT->bind(s, "material.diffuseTexture", 1);
  if (specularTextureT)
    specularTextureT->bind(s, "material.specularTexture", 2);
}

void Material::unbind() {
  if (specularTextureT)
    specularTextureT->unbind();
  else if (diffuseTextureT)
    diffuseTextureT->unbind();
  else if (ambientTextureT)
    ambientTextureT->unbind();
}

} // namespace Johnny