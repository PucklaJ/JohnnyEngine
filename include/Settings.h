#pragma once

namespace Johnny
{
	class MainClass;

	enum SettingName
	{
		VSYNC,
		MSAA,
		MSAA_SAMPLES
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

		static bool m_initialized;

		friend class MainClass;
	};
}