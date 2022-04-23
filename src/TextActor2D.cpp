#include "../include/TextActor2D.h"
#include "../include/Camera2D.h"
#include "../include/MainClass.h"
#include "../include/ResourceManager.h"
#include "../include/Texture.h"
#include <iostream>

namespace Johnny {
TextActor2D::TextActor2D(TTF_Font *font, const SDL_Color &color,
                         const std::string &text)
    : Sprite2D(), m_text(text), m_font(font), m_color(color) {
  setName(text.c_str());
}

TextActor2D::~TextActor2D() {}

bool TextActor2D::init() {
  Sprite2D::init();

  generateText();

  return true;
}

bool TextActor2D::update() {
  Sprite2D::update();

  if (m_needsUpdate) {
    generateText();
    m_needsUpdate = false;
  }
  return true;
}

void TextActor2D::quit() {
  Sprite2D::quit();

  if (!m_mainClass->getResourceManager()->isLoaded(m_font)) {
    TTF_CloseFont(m_font);
    m_font = nullptr;
  }
}

void TextActor2D::generateText() {
  if (m_mainClass) {
    Flip prevFlip = Flip::NONE;
    DrawModes prevDrawModes = DrawModes::BLENDING;
    Colorb prevKeyColor(0, 0, 0, 0);
    Colorb prevModColor(255, 255, 255, 255);

    if (m_texture) {
      prevFlip = m_texture->getFlip();
      prevDrawModes = m_texture->getDrawMode();
      prevKeyColor = m_texture->getKeyColor();
      prevModColor = m_texture->getModColor();

      delete m_texture;
      m_texture = nullptr;
    }

    SDL_Surface *sur = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(),
                                                      m_color, INT_MAX);

    setTexture(Texture::SDL_SurfaceToTexture(sur));

    m_texture->setFlip(prevFlip);
    m_texture->setDrawMode(prevDrawModes);
    m_texture->setKeyColor(prevKeyColor);
    m_texture->setModColor(prevModColor);

    SDL_FreeSurface(sur);
  }
}

} // namespace Johnny
