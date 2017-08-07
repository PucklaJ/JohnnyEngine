#include "../include/Sprite2D.h"
#include "../include/MainClass.h"
#include "../include/ResourceManager.h"
#include "../include/LogManager.h"

namespace Johnny
{
	Sprite2D::Sprite2D() : Sprite2D(nullptr)
	{
		m_castsShadows = false;
	}

	Sprite2D::Sprite2D(const std::string& fileName) : Actor("Sprite2D"),
		m_fileName(fileName)
	{
	}

	Sprite2D::Sprite2D(Texture* texture) : Actor("Sprite2D")
	{
		setTexture(texture);
	}

	Sprite2D::~Sprite2D()
	{
	}

	bool Sprite2D::init()
	{
		if (!Texture::getTexture2DShader())
			LogManager::error("Couldn't initialise Sprite2D! You have to add INIT_2D to the InitFlags!");

		setPosition(m_transform.getTranslation());
		setShader(Texture::getTexture2DShader());

		if (!m_texture && m_fileName != "")
		{
			setTexture(m_mainClass->getResourceManager()->loadTexture(m_fileName));
		}

		return true;
	}

	bool Sprite2D::update()
	{
		return true;
	}

	bool Sprite2D::render()
	{
		Texture::renderTexture2D(m_texture, m_isAffectedByCamera ? m_transform.getProjectedTransformation(m_mainClass->getCamera2D()) : m_transform.getTransformation(),false);

		return true;
	}

	void Sprite2D::quit()
	{
		if (!m_mainClass->getResourceManager()->isLoaded(m_texture))
		{
			delete m_texture;
			m_texture = nullptr;
		}
	}

	void Sprite2D::setTexture(Texture* texture)
	{
		if (texture)
		{
			m_texture = texture;
			setSize((GLfloat)m_texture->getWidth(), (GLfloat)m_texture->getHeight());
		}
	}
}


