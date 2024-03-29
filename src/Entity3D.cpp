#include "../include/Entity3D.h"
#include "../include/MainClass.h"
#include "../include/Mesh3D.h"
#include "../include/Model3D.h"
#include "../include/RenderManager.h"
#include "../include/ResourceManager.h"
#include "../include/Shader.h"
#include <iostream>

namespace Johnny {
Entity3D::Entity3D(const std::string &fileName)
    : Actor("Entity"), m_fileName(fileName) {}

Entity3D::Entity3D(Mesh3D *mesh) : Actor(mesh->getName().c_str()) {
  m_model = new Model3D();
  m_model->addMesh(mesh);
}

Entity3D::Entity3D(Model3D *m) : Actor(m->getName().c_str()), m_model(m) {
  m_transform = m->getTransform();
}

Entity3D::~Entity3D() {}

bool Entity3D::init() {
  if (m_fileName != "") {
    Mesh3D *m = m_mainClass->getResourceManager()->loadMesh(m_fileName);
    m_model = new Model3D();
    m_model->addMesh(m);
  }

  if (m_shader == nullptr) {
    setShader(RenderManager::DEFAULT_SHADER);
  } else {
    m_mainClass->getRenderManager()->addActor(this);
  }
  return true;
}

bool Entity3D::update() { return true; }

bool Entity3D::render() {
  /*if (!m_shader->isShadowMap())
m_shader->setUniform("transform",m_isAffectedByCamera ?
m_transform.getProjectedTransformation(m_mainClass->getCamera3D()) :
m_transform.getTransformation());

  m_shader->setUniform("worldMatrix", m_transform.getTransformation());*/

  m_shader->getShaderUpdater()->setUniforms(
      &m_transform, m_isAffectedByCamera ? ShaderUpdater::TRANSFORM_CAMERA
                                         : ShaderUpdater::TRANSFORM_NORMAL);
  m_shader->getShaderUpdater()->setUniforms(&m_transform,
                                            ShaderUpdater::TRANSFORM_WORLD);
  m_shader->getShaderUpdater()->setUniforms(this);

  return true;
}

void Entity3D::quit() {}

} // namespace Johnny
