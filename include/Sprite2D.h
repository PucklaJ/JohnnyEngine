#pragma once
#include "Actor.h"
#include "Transform2D.h"
#include <string>
#include "Texture.h"

namespace Johnny
{
	class Sprite2D : public Actor, public TransformableObject2D
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

		Texture* getTexture() { return m_texture; }

	protected:
		Texture* m_texture = nullptr;
	private:
		std::string m_fileName = "";
	};
}



