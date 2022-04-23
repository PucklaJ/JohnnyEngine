#pragma once
#include "OBJLoader.h"
#include "Vector2.h"
#include "Vector3.h"
#include <GL/glew.h>
#include <assimp/scene.h>

namespace Johnny {
class ResourceManager;
class Vertex3D;
class Shader;

/*! \brief A class which represents a bunch of vertices with a material on the
 * graphics card
 *
 */
class Mesh3D {
public:
  static Mesh3D *plane(const Vector2f &size);
  static Mesh3D *box(const Vector3f &size);

  Mesh3D();
  /*! \brief Creates a Mesh3D from a aiMesh
   *  \param mesh The aiMesh from which to take the data
   *  \param scene The aiScene to which to aiMesh belongs
   *  \param switchZandY Defines if it should switch the z and y-Axises of the
   * vertex positions
   */
  Mesh3D(aiMesh *mesh, const aiScene *scene, bool switchZandY);
  ~Mesh3D();

  /*! \brief Adds a number of vertices to the buffer
   *  \param v An array of vertices to load into the buffer
   *  \param vsize The number of vertices
   *  \param indices An array of indices to load into the element array buffer
   *  \param isize The number of indices
   */
  void addVertices(Vertex3D *v, unsigned int vsize, GLuint *indices,
                   unsigned int isize);
  /*! \brief Sets the Material
   *  \param mat The Material to set
   */
  void setMaterial(const Material &mat);
  /*! \brief Loads the textures of th material
   *  \param res The ResourceManager from which to load
   */
  void loadMaterial(ResourceManager *res);
  /*! \brief Renders the mesh to the active frame buffer
   *  \param s The Shader to which the material data should be loaded
   */
  void render(Shader *s = nullptr);

  const std::string &getName() const { return m_name; }
  const Material &getMaterial() const { return m_material; }

private:
  GLuint m_vbo = 0;              //!< The name of the vertex buffer
  GLuint m_ibo = 0;              //!< The name of the index buffer
  GLuint m_vao = 0;              //!< The vertex array object of the mesh
  unsigned int m_vertexSize = 0; //!< The number of vertices in the buffer
  unsigned int m_indexSize = 0;  //!< The number of indices in the buffer
  Material m_material;           //!< The material of the mesh
  std::string m_name = "NONE";   //!< The name of the mesh
};
} // namespace Johnny
