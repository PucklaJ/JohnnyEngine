#include "../include/Settings.h"
#include <SDL2/SDL_video.h>
#include "../include/RenderUtil.h"
#include "../include/LogManager.h"
#include <GL/glew.h>

namespace Johnny
{
	bool Settings::m_vsync = true;
	bool Settings::m_msaa = true;
	int Settings::m_msaa_samples = 8;
	bool Settings::m_initialized = false;

	bool Settings::seti(SettingName name, int value)
	{
		switch (name)
		{
		case MSAA_SAMPLES:
			if (m_initialized)
				return false;
			m_msaa_samples = value;
			break;
		default:return false;
		}

		return true;
	}

	bool Settings::setb(SettingName name, bool value)
	{
		switch (name)
		{
		case VSYNC:
			if (m_initialized)
			{
				if (m_vsync != value)
				{
					if (value)
					{
						if (SDL_GL_SetSwapInterval(-1) < 0)
							ERROR_OUT(SDL_GL_SetSwapInterval(1));
					}
					else
					{
						SDL_GL_SetSwapInterval(0);
					}

					m_vsync = value;
				}
			}
			else
			{
				m_vsync = value;
			}
			break;
		case MSAA:
			if (m_initialized)
			{
				if (m_msaa != value)
				{
					if (value)
						glEnable(GL_MULTISAMPLE);
					else
						glDisable(GL_MULTISAMPLE);

					m_msaa = value;
				}
			}
			else
			{
				m_msaa = value;
			}
		default:return false;
		}

		return true;
	}

	bool Settings::getb(SettingName name)
	{
		switch (name)
		{
		case VSYNC:
			return m_vsync;
		case MSAA:
			return m_msaa;
		default:return false;
		}
	}

	int Settings::geti(SettingName name)
	{
		switch (name)
		{
		case MSAA_SAMPLES:
			return m_msaa_samples;
		default: return 0;
		}
	}
}