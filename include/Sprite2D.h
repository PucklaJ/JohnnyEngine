#pragma once
#include "Actor.h"
#include <string>
#include "Texture.h"
#include "Geometry.h"
#include "Tween.h"

namespace Johnny
{
	class Sprite2D : public Actor, public TweenableObject2D
	{
	public:
		Sprite2D();
		Sprite2D(const std::string&);
		Sprite2D(Texture*);
		~Sprite2D();

		bool init() override;
		bool update() override;
		bool render() override;
		void quit() override;

		void setTexture(Texture*);
		void setSrcRegion(const TextureRegion&);
		void setDrawSize(const Vector2f&);
		void setDrawSize(GLfloat, GLfloat);

		Texture* getTexture() { return m_texture; }
		const TextureRegion& getSrcRegion() const { return m_srcRegion; }
		Vector2f getDrawSize() const;
		Vector2f getActualSize() const;
		Rectangle<GLfloat> getBoundingBox();

	protected:
		Texture* m_texture = nullptr;
	private:
		std::string m_fileName = "";
		TextureRegion m_srcRegion;
		Vector2f m_drawScale;
	};
}



