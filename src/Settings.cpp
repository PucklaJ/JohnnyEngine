#include "../include/Settings.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/RenderUtil.h"
#include <SDL2/SDL_video.h>

namespace Johnny {
bool Settings::m_vsync = true;
bool Settings::m_msaa = true;
int Settings::m_msaa_samples = 8;
bool Settings::m_initialized = false;
GLenum Settings::m_sprite2D_filtering = GL_NEAREST;
GLenum Settings::m_back_buffer_filtering = GL_LINEAR;

bool Settings::seti(SettingName name, int value) {
  switch (name) {
  case MSAA_SAMPLES:
    if (m_initialized)
      return false;
    m_msaa_samples = value;
    break;
  case SPRITE2D_FILTERING:
    if (m_initialized)
      return false;
    m_sprite2D_filtering = value;
    break;
  case BACK_BUFFER_FILTERING:
    m_back_buffer_filtering = value;
    if (m_initialized)
      MainClass::getInstance()->setNativeRes(
          MainClass::getInstance()->getNativeRes());
    break;
  default:
    return false;
  }

  return true;
}

bool Settings::setb(SettingName name, bool value) {
  switch (name) {
  case VSYNC:
    if (m_initialized) {
      if (m_vsync != value) {
        if (value) {
          if (SDL_GL_SetSwapInterval(-1) < 0)
            ERROR_OUT(SDL_GL_SetSwapInterval(1), "Couldn't enable VSYNC: ");
        } else {
          SDL_GL_SetSwapInterval(0);
        }

        m_vsync = value;
      }
    } else {
      m_vsync = value;
    }
    break;
  case MSAA:
    if (m_initialized) {
      if (m_msaa != value) {
        if (value)
          glEnable(GL_MULTISAMPLE);
        else
          glDisable(GL_MULTISAMPLE);

        m_msaa = value;
      }
    } else {
      m_msaa = value;
    }
    break;
  default:
    return false;
  }

  return true;
}

bool Settings::getb(SettingName name) {
  switch (name) {
  case VSYNC:
    return m_vsync;
  case MSAA:
    return m_msaa;
  default:
    return false;
  }
}

int Settings::geti(SettingName name) {
  switch (name) {
  case MSAA_SAMPLES:
    return m_msaa_samples;
  case SPRITE2D_FILTERING:
    return m_sprite2D_filtering;
  case BACK_BUFFER_FILTERING:
    return m_back_buffer_filtering;
  default:
    return 0;
  }
}
} // namespace Johnny
