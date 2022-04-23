#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "Colors.h"
#include <GL/glew.h>
#include <assimp/scene.h>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace Johnny {
class ResourceManager;
class Vertex3D;
class Texture;
class Shader;

/*! \brief A index which stores a vertex position index, vertex normal index and
 * a uvIndex DEPRECATED
 *
 */
class NormalPosUVIndex {
public:
  GLuint posIndex = 0;
  GLuint normalIndex = 0;
  GLuint uvIndex = 0;
  bool createNew = false;
  std::string material = "NONE";

  bool operator<(const NormalPosUVIndex &);
  bool operator>(const NormalPosUVIndex &);
  bool operator==(const NormalPosUVIndex &);
  bool operator<=(const NormalPosUVIndex &);
  bool operator>=(const NormalPosUVIndex &);
};

extern bool operator<(const NormalPosUVIndex &, const NormalPosUVIndex &);
extern bool operator>(const NormalPosUVIndex &, const NormalPosUVIndex &);
extern bool operator==(const NormalPosUVIndex &, const NormalPosUVIndex &);
extern bool operator<=(const NormalPosUVIndex &, const NormalPosUVIndex &);
extern bool operator>=(const NormalPosUVIndex &, const NormalPosUVIndex &);

/*! \brief A class which represents a bunch of textures a few colors and a few
 * numbers to define how a mesh looks
 *
 */
class Material {
public:
  Material();
  /*! \brief Creates a Material from a aiMaterial
   *  \param mat The aiMaterial to create from
   */
  Material(aiMaterial *mat);

  /*! \brief Load the uniform locations of the material values to a Shader
   *  \param s The Shader to load the locations to
   *  \param withTextures Defines wether the texture uniform sampler locations
   * should be included
   */
  static void setUniforms(Shader *s, bool withTextures = true);

  /*! \brief Loads a material from a material file (internal use only
   *  \param contents The contents of the material inside the file
   */
  void load(const std::string &contents);
  /*! \brief Loads the textures of the material
   *  \param res The ResourceManager from which to load
   */
  void loadTextures(ResourceManager *res);
  /*! \brief Loads the data as uniforms to a shader and binds the textures
   *  \param s The Shader to which to load
   */
  void bind(Shader *s);
  /*! \brief Unbinds the textures
   *
   */
  void unbind();

  std::string name = "NONE"; //!< The name of the material
  Colorf ambientColor =
      Colorf(1.0f, 1.0f, 1.0f); //!< The ambientColor of the material
  Colorf diffuseColor =
      Colorf(1.0f, 1.0f, 1.0f); //!< The diffuseColor of the material
  Colorf specularColor =
      Colorf(1.0f, 1.0f, 1.0f); //!< The specular color of the material
  Colorf emittedLight =
      Colorf(0.0f, 0.0f,
             0.0f); //!< The light which the material emits (will be ignored)
  GLfloat specularExponent =
      1.0f; //!< The specularExponent for the calculation of the specular light
  GLfloat transparency = 1.0f; //!< The transperancy of the material
  Colorf transmissionFilter = Colorf(
      1.0f, 1.0f,
      1.0f); //!< The transmissionFilter of the material (will be ignored)
  GLuint illumination =
      0; //!< The illumination of the material (will be ignored)
  std::string ambientTexture = "";  //!< The filePath of the ambient texture
  std::string diffuseTexture = "";  //!< The filePath of the diffuse texture
  std::string specularTexture = ""; //!< The filePath of the specular texture

  Texture *ambientTextureT = nullptr;  //!< The ambient texture of the material
  Texture *diffuseTextureT = nullptr;  //!< The diffuse texture of the material
  Texture *specularTextureT = nullptr; //!< The specular texture of the material
  bool hasTextures = false;            //!< Defines if the textures will be used
};

/*! \brief A class which loads .mtl files
 *
 */
class MTLLoader {
public:
  /*! \brief Creates a MTLLoader
   *  \param file The filePath of the .mtl file to load from
   */
  MTLLoader(const std::string &file);

  /*! \brief Loads the data frim the file
   *
   */
  void load();
  /*! \return The materials which have been loaded
   *
   */
  const std::vector<Material> &getMaterials() const { return m_materials; }

private:
  std::string m_fileName = "NONE";   //!< The file path of the .mtl file
  std::vector<Material> m_materials; //!< The materials which have been loaded
};

/*! \brief A class which loads .obj files
 *
 */
class OBJLoader {
public:
  /*! \brief Creates a new OBJlLoader
   *  \param file The file path of the .obj file
   */
  OBJLoader(const std::string &file);
  ~OBJLoader();

  /*! \brief Loads the data from the file
   *
   */
  void load();
  /*! \brief Clears the data which has been loaded
   *
   */
  void clear();

  /*! \return The vertices loaded
   *
   */
  Vertex3D *getVertices() { return m_vertices; }
  /*! \return The indices loaded
   *
   */
  GLuint *getInidices() { return m_indices; }
  /*! \return The materials loaded
   *
   */
  const std::vector<Material> &getMaterials() const { return m_materials; }

  /*! \return The number vertices loaded
   *
   */
  unsigned int getVerticesSize() { return m_vertSize; }
  /*! \return The number of indices loaded
   *
   */
  unsigned int getIndicesSize() { return m_indSize; }

private:
  /*! \brief Detect if a tuple of GLuints is inside a map
   *  \param Map The map from which to look
   *  \param value The value to look after
   */
  bool findInMap(std::map<std::tuple<GLuint, GLuint, GLuint>, GLuint> &Map,
                 const std::tuple<GLuint, GLuint, GLuint> &value);

  std::string m_fileName = "NONE";   //!< The file path of the .obj file
  Vertex3D *m_vertices = nullptr;    //!< The verticecs loaded
  GLuint *m_indices = nullptr;       //!< The indices loaded
  unsigned int m_vertSize = 0;       //!< The number of vertices loaded
  unsigned int m_indSize = 0;        //!< The number of indices loaded
  std::vector<Material> m_materials; //!< The materials loaded
};
} // namespace Johnny

#endif
