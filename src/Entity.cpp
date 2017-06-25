#include <Entity.h>
#include <MainClass.h>
#include <ResourceManager.h>
#include <Mesh.h>
#include <Shader.h>
#include <iostream>
#include <RenderManager.h>
#include <Model.h>

Entity::Entity(const std::string& fileName) : SDL::Actor("Entity"),
	m_fileName(fileName)
{
}

Entity::Entity(Mesh* mesh) : SDL::Actor(mesh->getName().c_str())
{
	m_model = new Model();
	m_model->addMesh(mesh);
}

Entity::Entity(Model* m) : SDL::Actor(m->getName().c_str()),
	m_model(m)
{
	m_transform = m->getTransform();
}

Entity::~Entity()
{
}

bool Entity::init()
{
	if (m_fileName != "")
	{
		Mesh* m = m_mainClass->getResourceManager()->loadMesh(m_fileName);
		m_model = new Model();
		m_model->addMesh(m);
	}

	if (m_shader == nullptr)
	{
		setShader(RenderManager::DEFAULT_SHADER);
	}
	else
	{
		m_mainClass->getRenderManager()->addActor(this);
	}

	return true;
}

bool Entity::update()
{
	return true;
}

bool Entity::render()
{
	if(!m_shader->isShadowMap())
		m_shader->setUniformMat4("transform", m_isAffectedByCamera ? m_transform.getProjectedTransformation(m_mainClass->getCamera()) : m_transform.getTransformation());
	m_shader->setUniformMat4("worldMatrix", m_transform.getTransformation());

	m_model->render(m_shader);

	return true;
}

void Entity::quit()
{
	
}
