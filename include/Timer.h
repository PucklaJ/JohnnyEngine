#pragma once
#include <chrono>
#include "../include/SDL2_framerate.h"

#define NO_FPS_LOCK -1

using namespace std;
using namespace chrono;

namespace Johnny
{
	/*! \brief A class for measuring time, smoothing the timestep and locking the framerate
	 *
	 */
	class Timer
	{
	public:
		Timer();
		~Timer();

		/*! \brief Sets the value which will be multiplied on the delta time
		 *  \param d The value which will be used for the multiplication
		 */
		void setTimeScale(double d) { m_timeScale = d; }
		/*! \brief Defines on which FPS it should lock or if it shouldn't lock the framerate
		 *  \param The frame rate to lock
		 */
		void setMaxFPS(int maxFPS);

/*#ifdef _WIN32
		float getDeltaTimeInSeconds() const { return (float)(m_realDeltaTimeInSeconds*m_timeScale); }
#else*/
		/*! \return The time between the last frame and this frame but smoothed over multiple frames
		 *
		 */
		float getDeltaTimeInSeconds() const { return (float)(m_smoothDeltaTimeInSeconds*m_timeScale); }
//#endif
		/*! \return The frames per second
		 *
		 */
		double getFPS() const { return m_fps; }
		/*! \return The frame rate on which it should lock
		 *
		 */
		int getMaxFPS() { return m_maxFPS; }

		/*! \brief Starts the time measurment
		 *
		 */
		void startTimeMeasure();
		/*! \brief Ends the time measurement, calculates the smoothed delta time and locks the frame rate
		 *  \return The frames per second
		 */
		int endTimeMeasure();
	private:
		int m_maxFPS = 60;																	 		 //!< The FPS at which it should lock
		double m_timeScale = 1.0;																	 //!< The value which will be multiplied onto the delta time
		double calculateMeanDeltaTime();															 //!< Caclulates the average of the last frames
		void takeAwayHighestAndLowestDts();															 //!< Takes away the two hightest and lowest delta times from the array
		void moveDeltaTimesOneIndexDown();															 //!< Shifts the delta times one index down on the array
		int getDeltaTimesSize();																	 //!< Gets the number of frame times saved in the array
		void copyRealTimesToSmoothTimes();															 //!< Copies the measured delta times array into the smoothed delta times array
		int m_realDeltaTimeSize = 0;																 //!< The number of real delta times measured
		void setNum(double&, int&);																     //!< Sets a number
		double m_realDeltaTimeInSeconds = 0.0;														 //!< The delta time measured
		double m_smoothDeltaTimeInSeconds = 0.0;													 //!< The delta time smoothed by the calculations
		double m_realDeltaTimes[11] = { -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0 };    //!< The array of real measured delta times
		double m_smoothDeltaTimes[11] = { -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0 };  //!< The array of smoothed delta times
		double m_FPSes[3];																			 //!< The frames per second of the last frames
		double m_fps = 0.0;																			 //!< The fps averaged over the last three frames
		int m_lastFrame = 0;																		 //!< The number of the last frame
		double m_time = 0.0;																		 //!< The time
		high_resolution_clock::time_point m_startTime;												 //!< A high_resolution clock for measuring the time
		high_resolution_clock::time_point m_endTime;												 //!< A high_resolution clock for measuring the time
#ifdef MAX_FPS_LOCK
		double m_timeForMaxFPS = 0.0;
		high_resolution_clock::time_point m_startTimeForMaxFPS;
		high_resolution_clock::time_point m_endTimeForMaxFPS;
		duration<double, micro> m_deltaClockTimeForMaxFPS;
#endif
		duration<double, micro> m_deltaClockTime;												     //!< A duration for measuring the time

		FPSmanager m_fpsManager;																	 //!< The FPSManager which locks the frame rate
	};
}