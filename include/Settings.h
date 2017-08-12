#pragma once
#include <GL/glew.h>

namespace Johnny
{
	class MainClass;

	enum SettingName
	{
		VSYNC,
		MSAA,
		MSAA_SAMPLES,
		SPRITE2D_FILTERING,
		BACK_BUFFER_FILTERING
	};

	class Settings
	{
	public:
		static bool seti(SettingName,int);
		static bool setb(SettingName,bool);

		static bool getb(SettingName);
		static int geti(SettingName);
	private:
		static bool m_vsync;
		static bool m_msaa;
		static int m_msaa_samples;
		static GLenum m_sprite2D_filtering;
		static GLenum m_back_buffer_filtering;

		static bool m_initialized;

		friend class MainClass;
	};
}