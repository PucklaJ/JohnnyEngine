#include "Timer.h"
#include "LogManager.h"

namespace Johnny
{
	Timer::Timer()
	{
		m_FPSes[0] = m_FPSes[1] = m_FPSes[2] = 0.0;

		SDL_initFramerate(&m_fpsManager);
		SDL_setFramerate(&m_fpsManager, m_maxFPS);
	}

	Timer::~Timer()
	{

	}

	void Timer::startTimeMeasure()
	{
		m_startTime = high_resolution_clock::now();
	}

	int Timer::endTimeMeasure()
	{
		if (m_maxFPS != NO_FPS_LOCK)
			SDL_framerateDelay(&m_fpsManager);

		m_endTime = high_resolution_clock::now();
		m_deltaClockTime = m_endTime - m_startTime;
		m_realDeltaTimeInSeconds = m_deltaClockTime.count() / 1000000.0;

		m_realDeltaTimeSize = getDeltaTimesSize();
		if (m_realDeltaTimeSize == 11)
			moveDeltaTimesOneIndexDown();

		// Set the last frameTime
		m_realDeltaTimes[m_realDeltaTimeSize == 11 ? 10 : m_realDeltaTimeSize] = m_realDeltaTimeInSeconds;

		// Copy Real Frame Times into the smooth ones
		copyRealTimesToSmoothTimes();

		// Calculate the mean Time
		m_smoothDeltaTimeInSeconds = calculateMeanDeltaTime();

		m_FPSes[m_lastFrame] = 1.0 / m_smoothDeltaTimeInSeconds;

		m_lastFrame++;
		if (m_lastFrame == 3)
		{
			m_lastFrame = 0;
		}


		m_fps = (int)((m_FPSes[0] + m_FPSes[1] + m_FPSes[2]) / 3.0);

		return (int)m_fps;
	}

	void Timer::copyRealTimesToSmoothTimes()
	{
		for (int i = 0; i<11; i++)
		{
			m_smoothDeltaTimes[i] = m_realDeltaTimes[i];
		}
	}


	int Timer::getDeltaTimesSize()
	{
		for (int i = 0; i<11; i++)
		{
			if (m_realDeltaTimes[i] == -1.0)
				return i;
		}

		return 11;
	}


	void Timer::moveDeltaTimesOneIndexDown()
	{
		for (int i = 0; i<11; i++)
		{
			if (i > 0)
				m_realDeltaTimes[i - 1] = m_realDeltaTimes[i];
		}

		m_realDeltaTimes[10] = -1.0;
	}


	double Timer::calculateMeanDeltaTime()
	{
		double mean = 0.0;
		int size = 11;

		for (int i = 0; i<11; i++)
		{
			if (m_smoothDeltaTimes[i] == -1.0)
			{
				size = i;
				break;
			}
		}

		if (size > 4)
		{
			takeAwayHighestAndLowestDts();
		}

		for (int i = 0; i<11; i++)
		{
			if (m_smoothDeltaTimes[i] != -1.0)
			{
				mean += m_smoothDeltaTimes[i];
			}
		}

		return mean / (size > 4 ? 7.0 : (double)size);
	}

	void Timer::takeAwayHighestAndLowestDts()
	{
		int numIndex = 0;
		double num = 0;

		// Take away two Lowest
		for (int j = 0; j<2; j++)
		{
			setNum(num, numIndex);
			for (int i = 0; i<11; i++)
			{
				if (m_smoothDeltaTimes[i] != -1.0)
				{
					if (m_smoothDeltaTimes[i] < num)
					{
						num = m_smoothDeltaTimes[i];
						numIndex = i;
					}
				}
			}

			m_smoothDeltaTimes[numIndex] = -1.0;

		}


		numIndex = 0;


		//Take away two highest
		for (int j = 0; j<2; j++)
		{
			setNum(num, numIndex);
			for (int i = 0; i<11; i++)
			{
				if (m_smoothDeltaTimes[i] != -1.0)
				{
					if (m_smoothDeltaTimes[i] > num)
					{
						num = m_smoothDeltaTimes[i];
						numIndex = i;
					}
				}
			}

			m_smoothDeltaTimes[numIndex] = -1.0;
		}

	}

	void Timer::setNum(double& num, int& numIndex)
	{
		for (int i = 0; i<11; i++)
		{
			if (m_smoothDeltaTimes[i] != -1.0)
			{
				num = m_smoothDeltaTimes[i];
				numIndex = i;
			}
		}
	}

	void Timer::setMaxFPS(int fps)
	{
		if (fps == NO_FPS_LOCK)
		{
			m_maxFPS = fps;
			return;
		}

		if (fps > FPS_UPPER_LIMIT)
		{
			fps = FPS_UPPER_LIMIT;
		}
		else if (fps < FPS_LOWER_LIMIT)
		{
			fps = FPS_LOWER_LIMIT;
		}

		m_maxFPS = fps;

		if (SDL_setFramerate(&m_fpsManager, m_maxFPS)<0)
		{
			LogManager::error("Setting max FPS");
		}
	}
}