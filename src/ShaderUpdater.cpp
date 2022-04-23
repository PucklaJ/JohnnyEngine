#include "../include/ShaderUpdater.h"
#include "../include/Camera3D.h"
#include "../include/Entity3D.h"
#include "../include/Light3D.h"
#include "../include/MainClass.h"
#include "../include/Mesh3D.h"
#include "../include/Model3D.h"
#include "../include/OBJLoader.h"
#include "../include/Shader.h"

namespace Johnny {
const unsigned int ShaderUpdater::TRANSFORM_NORMAL = 0;
const unsigned int ShaderUpdater::TRANSFORM_CAMERA = 1;
const unsigned int ShaderUpdater::TRANSFORM_WORLD = 2;

ShaderUpdater::ShaderUpdater(Shader *s) : m_shader(s) {}

ShaderUpdater::~ShaderUpdater() {}

void ShaderUpdater::setUniforms(Model3D *model, const unsigned int index) {
  for (size_t i = 0; i < model->getMeshes().size(); i++) {
    setUniforms(model->getMeshes()[i], index);
  }
}

void ShaderUpdater::setUniforms(Material *material, const unsigned int index) {
  material->bind(m_shader);
}

void ShaderUpdater::setUniforms(Mesh3D *m, const unsigned int index) {
  setUniforms(const_cast<Material *>(&m->getMaterial()), index);
}

void ShaderUpdater::setUniforms(Lighting3D *m, const unsigned int index) {
  m_shader->setUniform("ambientLight",
                       Vector4f(Lighting3D::ambientLight.normalise()));
  m->load(m_shader, 3);
}

void ShaderUpdater::setUniforms(Camera3D *m, const unsigned int index) {
  m_shader->setUniform("eyePosition", m->getPosition());
}

void ShaderUpdater::setUniforms(Entity3D *m, const unsigned int index) {
  m->getModel()->render(m_shader);
}

void ShaderUpdater::setUniforms(Transform3D *m, const unsigned int index) {
  switch (index) {
  case TRANSFORM_NORMAL:
    m_shader->setUniform("transform", m->getTransformation());
    break;
  case TRANSFORM_CAMERA:
    m_shader->setUniform(
        "transform",
        m->getProjectedTransformation(MainClass::getInstance()->getCamera3D()));
    break;
  case TRANSFORM_WORLD:
    m_shader->setUniform("worldMatrix", m->getTransformation());
    break;
  }
}
} // namespace Johnny