#pragma once
#include <chrono>
#include "../include/SDL2_framerate.h"

#define NO_FPS_LOCK -1

using namespace std;
using namespace chrono;

namespace Johnny
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void setTimeScale(double d) { m_timeScale = d; }
		void setMaxFPS(int);

/*#ifdef _WIN32
		float getDeltaTimeInSeconds() const { return (float)(m_realDeltaTimeInSeconds*m_timeScale); }
#else*/
		float getDeltaTimeInSeconds() const { return (float)(m_smoothDeltaTimeInSeconds*m_timeScale); }
//#endif
		double getFPS() const { return m_fps; }
		int getMaxFPS() { return m_maxFPS; }

		void startTimeMeasure();
		int endTimeMeasure();
	private:
		int m_maxFPS = 60;
		double m_timeScale = 1.0;
		double calculateMeanDeltaTime();
		void takeAwayHighestAndLowestDts();
		void moveDeltaTimesOneIndexDown();
		int getDeltaTimesSize();
		void copyRealTimesToSmoothTimes();
		int m_realDeltaTimeSize = 0;
		void setNum(double&, int&);
		double m_realDeltaTimeInSeconds = 0.0;
		double m_smoothDeltaTimeInSeconds = 0.0;
		double m_realDeltaTimes[11] = { -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0 };
		double m_smoothDeltaTimes[11] = { -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0 };
		double m_FPSes[3];
		double m_fps = 0.0;
		int m_lastFrame = 0;
		double m_time = 0.0;
		high_resolution_clock::time_point m_startTime;
		high_resolution_clock::time_point m_endTime;
#ifdef MAX_FPS_LOCK
		double m_timeForMaxFPS = 0.0;
		high_resolution_clock::time_point m_startTimeForMaxFPS;
		high_resolution_clock::time_point m_endTimeForMaxFPS;
		duration<double, micro> m_deltaClockTimeForMaxFPS;
#endif
		duration<double, micro> m_deltaClockTime;

		FPSmanager m_fpsManager;
	};
}