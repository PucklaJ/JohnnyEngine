#include "../include/Mesh3D.h"
#include "../include/LogManager.h"
#include "../include/ResourceManager.h"
#include "../include/Shader.h"
#include "../include/Vertex3D.h"
#include <GL/glew.h>
#include <assimp/scene.h>
#include <iostream>

namespace Johnny {
Mesh3D *Mesh3D::plane(const Vector2f &size) {
  Mesh3D *planeMesh = new Mesh3D();

  Vertex3D vertices[4];
  GLuint indices[6];

  vertices[0].pos.x = -size.x / 2.0f;
  vertices[0].pos.y = 0.0f;
  vertices[0].pos.z = size.y / 2.0f;

  vertices[1].pos.x = size.x / 2.0f;
  vertices[1].pos.y = 0.0f;
  vertices[1].pos.z = size.y / 2.0f;

  vertices[2].pos.x = size.x / 2.0f;
  vertices[2].pos.y = 0.0f;
  vertices[2].pos.z = -size.y / 2.0f;

  vertices[3].pos.x = -size.x / 2.0f;
  vertices[3].pos.y = 0.0f;
  vertices[3].pos.z = -size.y / 2.0f;

  for (int i = 0; i < 4; i++) {
    vertices[i].normal.x = 0.0f;
    vertices[i].normal.y = 1.0f;
    vertices[i].normal.z = 0.0f;
  }

  vertices[0].uv.x = 0.0f;
  vertices[0].uv.y = 0.0f;

  vertices[1].uv.x = 1.0f;
  vertices[1].uv.y = 0.0f;

  vertices[2].uv.x = 1.0f;
  vertices[2].uv.y = 1.0f;

  vertices[3].uv.x = 0.0f;
  vertices[3].uv.y = 1.0f;

  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;
  indices[3] = 2;
  indices[4] = 3;
  indices[5] = 0;

  planeMesh->addVertices(vertices, 4, indices, 6);

  return planeMesh;
}

Mesh3D *Mesh3D::box(const Vector3f &size) {
  Mesh3D *boxMesh = new Mesh3D();

  Vertex3D vertices[24];
  GLuint indices[36];

  /***** Positions ****/

  // BOTTOM_LEFT_FRONT
  vertices[0].pos.x = -size.x / 2.0f;
  vertices[0].pos.y = -size.y / 2.0f;
  vertices[0].pos.z = size.z / 2.0f;

  vertices[8].pos = vertices[20].pos = vertices[0].pos;

  // BOTTOM_RIGHT_FRONT
  vertices[1].pos.x = size.x / 2.0f;
  vertices[1].pos.y = -size.y / 2.0f;
  vertices[1].pos.z = size.z / 2.0f;

  vertices[9].pos = vertices[12].pos = vertices[1].pos;

  // BOTTOM_RIGHT_BACK
  vertices[2].pos.x = size.x / 2.0f;
  vertices[2].pos.y = -size.y / 2.0f;
  vertices[2].pos.z = -size.z / 2.0f;

  vertices[13].pos = vertices[17].pos = vertices[2].pos;

  // BOTTOM_LEFT_BACK
  vertices[3].pos.x = -size.x / 2.0f;
  vertices[3].pos.y = -size.y / 2.0f;
  vertices[3].pos.z = -size.z / 2.0f;

  vertices[16].pos = vertices[21].pos = vertices[3].pos;

  // TOP_LEFT_FRONT
  vertices[4].pos.x = -size.x / 2.0f;
  vertices[4].pos.y = size.y / 2.0f;
  vertices[4].pos.z = size.z / 2.0f;

  vertices[11].pos = vertices[23].pos = vertices[4].pos;

  // TOP_RIGHT_FRONT
  vertices[5].pos.x = size.x / 2.0f;
  vertices[5].pos.y = size.y / 2.0f;
  vertices[5].pos.z = size.z / 2.0f;

  vertices[10].pos = vertices[15].pos = vertices[5].pos;

  // TOP_RIGHT_BACK
  vertices[6].pos.x = size.x / 2.0f;
  vertices[6].pos.y = size.y / 2.0f;
  vertices[6].pos.z = -size.z / 2.0f;

  vertices[14].pos = vertices[18].pos = vertices[6].pos;

  // TOP_LEFT_BACK
  vertices[7].pos.x = -size.x / 2.0f;
  vertices[7].pos.y = size.y / 2.0f;
  vertices[7].pos.z = -size.z / 2.0f;

  vertices[19].pos = vertices[22].pos = vertices[7].pos;

  /****** Indices ******/

  // BOTTOM
  indices[0] = 0;
  indices[1] = 3;
  indices[2] = 2;
  indices[3] = 2;
  indices[4] = 1;
  indices[5] = 0;

  // TOP
  indices[6] = 4;
  indices[7] = 5;
  indices[8] = 6;
  indices[9] = 6;
  indices[10] = 7;
  indices[11] = 4;

  // FRONT
  indices[12] = 8;
  indices[13] = 9;
  indices[14] = 10;
  indices[15] = 10;
  indices[16] = 11;
  indices[17] = 8;

  // RIGHT
  indices[18] = 12;
  indices[19] = 13;
  indices[20] = 14;
  indices[21] = 14;
  indices[22] = 15;
  indices[23] = 12;

  // BACK
  indices[24] = 17;
  indices[25] = 16;
  indices[26] = 19;
  indices[27] = 19;
  indices[28] = 18;
  indices[29] = 17;

  // LEFT
  indices[30] = 21;
  indices[31] = 20;
  indices[32] = 23;
  indices[33] = 23;
  indices[34] = 22;
  indices[35] = 21;

  /****** Normals ******/

  // BOTTOM
  for (int i = 0; i < 4; i++) {
    vertices[i].normal.x = 0.0f;
    vertices[i].normal.y = -1.0f;
    vertices[i].normal.z = 0.0f;
  }

  // TOP
  for (int i = 4; i < 8; i++) {
    vertices[i].normal.x = 0.0f;
    vertices[i].normal.y = 1.0f;
    vertices[i].normal.z = 0.0f;
  }

  // FRONT
  for (int i = 12; i < 18; i++) {
    vertices[indices[i]].normal.x = 0.0f;
    vertices[indices[i]].normal.y = 0.0f;
    vertices[indices[i]].normal.z = 1.0f;
  }

  // RIGHT
  for (int i = 18; i < 24; i++) {
    vertices[indices[i]].normal.x = 1.0f;
    vertices[indices[i]].normal.y = 0.0f;
    vertices[indices[i]].normal.z = 0.0f;
  }

  // BACK
  for (int i = 24; i < 30; i++) {
    vertices[indices[i]].normal.x = 0.0f;
    vertices[indices[i]].normal.y = 0.0f;
    vertices[indices[i]].normal.z = -1.0f;
  }

  // LEFT
  for (int i = 30; i < 36; i++) {
    vertices[indices[i]].normal.x = -1.0f;
    vertices[indices[i]].normal.y = 0.0f;
    vertices[indices[i]].normal.z = 0.0f;
  }

  /****** UV *****/

  // BOT
  vertices[0].uv = Vector2f(0.0f, 1.0f);
  vertices[1].uv = Vector2f(1.0f / 3.0f, 1.0f);
  vertices[2].uv = Vector2f(1.0f / 3.0f, 0.5f);
  vertices[3].uv = Vector2f(0.0f, 0.5f);

  // TOP
  vertices[4].uv = Vector2f(1.0f / 3.0f, 1.0f);
  vertices[5].uv = Vector2f(2.0f / 3.0f, 1.0f);
  vertices[6].uv = Vector2f(2.0f / 3.0f, 0.5f);
  vertices[7].uv = Vector2f(1.0f / 3.0f, 0.5f);

  // FRONT
  vertices[8].uv = Vector2f(2.0f / 3.0f, 1.0f);
  vertices[9].uv = Vector2f(1.0f, 1.0f);
  vertices[10].uv = Vector2f(1.0f, 0.5f);
  vertices[11].uv = Vector2f(2.0f / 3.0f, 0.5f);

  // RIGHT
  vertices[12].uv = Vector2f(2.0f / 3.0f, 0.5f);
  vertices[13].uv = Vector2f(1.0f, 0.5f);
  vertices[14].uv = Vector2f(1.0f, 0.0f);
  vertices[15].uv = Vector2f(2.0f / 3.0f, 0.0f);

  // BACK
  vertices[16].uv = Vector2f(2.0f / 3.0f, 0.5f);
  vertices[17].uv = Vector2f(1.0f / 3.0f, 0.5f);
  vertices[18].uv = Vector2f(1.0f / 3.0f, 0.0f);
  vertices[19].uv = Vector2f(2.0f / 3.0f, 0.0f);

  // LEFT
  vertices[20].uv = Vector2f(1.0f / 3.0f, 0.5f);
  vertices[21].uv = Vector2f(0.0f, 0.5f);
  vertices[22].uv = Vector2f(0.0f, 0.0f);
  vertices[23].uv = Vector2f(1.0f / 3.0f, 0.0f);

  boxMesh->addVertices(vertices, 24, indices, 36);

  return boxMesh;
}

Mesh3D::Mesh3D() {
  glGenBuffers(1, &m_vbo);
  if (m_vbo == 0) {
    Johnny::LogManager::error("Couldn't create VertexBuffer for Mesh", true,
                              true, false);
  } else {
    glGenBuffers(1, &m_ibo);
    if (m_ibo == 0) {
      Johnny::LogManager::error("Couldn't create IndexBuffer for Mesh", true,
                                true, false);
    } else {
      glGenVertexArrays(1, &m_vao);
      if (m_vao == 0) {
        Johnny::LogManager::error("Couldn't create VertexArrays for Mesh", true,
                                  true, false);
      }
    }
  }

  m_material.name = "NONE";
}

Mesh3D::Mesh3D(aiMesh *mesh, const aiScene *scene, bool switchZandY)
    : Mesh3D() {

  m_material = Material(scene->mMaterials[mesh->mMaterialIndex]);
  if (m_material.name == "NONE")
    m_material.name = "Material";

  m_name = mesh->mName.C_Str();
  if (m_name == "")
    m_name = "NONE";

  std::vector<Vertex3D> vertices;
  std::vector<GLuint> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex3D vert;

    if (mesh->HasPositions()) {
      vert.pos.x = mesh->mVertices[i].x;
      if (switchZandY) {
        vert.pos.y = mesh->mVertices[i].z;
        vert.pos.z = -mesh->mVertices[i].y;
      } else {
        vert.pos.y = mesh->mVertices[i].y;
        vert.pos.z = mesh->mVertices[i].z;
      }
    }

    if (mesh->HasTextureCoords(0)) {
      if (mesh->mTextureCoords && mesh->mTextureCoords[0]) {
        vert.uv.x = mesh->mTextureCoords[0][i].x;
        vert.uv.y = mesh->mTextureCoords[0][i].y;
      } else {
        vert.uv.x = vert.uv.y = 0.0f;
      }
    }

    if (mesh->HasNormals()) {
      vert.normal.x = mesh->mNormals[i].x;
      if (switchZandY) {
        vert.normal.y = mesh->mNormals[i].z;
        vert.normal.z = -mesh->mNormals[i].y;
      } else {
        vert.normal.y = mesh->mNormals[i].y;
        vert.normal.z = mesh->mNormals[i].z;
      }
    }

    vertices.push_back(vert);
  }

  aiFace face;

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  Vertex3D *verticesArray = new Vertex3D[vertices.size()];
  GLuint *indicesArray = new GLuint[indices.size()];

  for (size_t i = 0; i < vertices.size(); i++) {
    verticesArray[i] = vertices[i];
  }

  for (size_t i = 0; i < indices.size(); i++) {
    indicesArray[i] = indices[i];
  }

  addVertices(verticesArray, (unsigned int)vertices.size(), indicesArray,
              (unsigned int)indices.size());

  delete[] verticesArray;
  delete[] indicesArray;
}

Mesh3D::~Mesh3D() {
  if (m_vbo != 0) {
    glDeleteBuffers(1, &m_vbo);
  }

  if (m_ibo != 0) {
    glDeleteBuffers(1, &m_ibo);
  }

  if (m_vao != 0) {
    glDeleteVertexArrays(1, &m_vao);
  }
}

void Mesh3D::addVertices(Vertex3D *vertices, unsigned int size, GLuint *indices,
                         unsigned int indexSize) {
  if (m_vbo == 0 || m_ibo == 0 || m_vao == 0) {
    Johnny::LogManager::error(
        "Couldn't add Vertices, because the Buffers aren't initialized");
    return;
  }

  m_vertexSize = size * Vertex3D::SIZE;
  m_indexSize = indexSize;

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertexSize * sizeof(GLfloat), vertices,
               GL_STATIC_DRAW);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexSize * sizeof(GLuint), indices,
               GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(m_vao);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  Vertex3D::setVertexAttribPointer();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

  glBindVertexArray(0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh3D::setMaterial(const Material &mat) { m_material = mat; }

void Mesh3D::loadMaterial(Johnny::ResourceManager *res) {
  m_material.loadTextures(res);
}

void Mesh3D::render(Shader *s) {
  if (m_vbo != 0 && m_ibo != 0 && m_vao != 0) {
    glBindVertexArray(m_vao);

    if (s) {
      s->getShaderUpdater()->setUniforms(this);
      glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
    } else {
      glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
  }
}

} // namespace Johnny