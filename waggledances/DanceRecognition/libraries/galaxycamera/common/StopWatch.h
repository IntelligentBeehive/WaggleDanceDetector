//----------------------------------------------------------------------------------
/**
\file     StopWatch.h
\brief  StopWatch class declaration
*/
//----------------------------------------------------------------------------------
#ifndef STOPWATCH_H
#define STOPWATCH_H

class CStopWatch
{ 
public: 

	/// Construction 
	CStopWatch()
	{ 
		Start(); 
	} 

	/// Start counting 
	void Start() 
	{ 
		QueryPerformanceCounter(&m_StartTime);
	} 

	/// Stop counting,ms
	double Stop() 
	{
		QueryPerformanceCounter(&m_StopTime);
		double theElapsedTime = __ElapsedTime();

		return theElapsedTime;
	} 

private:
	/// Get the time interval 
	double __ElapsedTime() 
	{ 
		LARGE_INTEGER timerFrequency; QueryPerformanceFrequency(&timerFrequency); 
		__int64 oldTicks = ((__int64)m_StartTime.HighPart << 32) + (__int64)m_StartTime.LowPart;
		__int64 newTicks = ((__int64)m_StopTime.HighPart << 32) + (__int64)m_StopTime.LowPart; 
		long double timeDifference = (long double) (newTicks - oldTicks); 
		long double ticksPerSecond = (long double) (((__int64)timerFrequency.HighPart << 32) + (__int64)timerFrequency.LowPart); 
		return (double)(timeDifference * 1000/ ticksPerSecond); 
	}
protected: 
	LARGE_INTEGER m_StartTime;    ///< Start time
	LARGE_INTEGER m_StopTime;     ///< Stop time
};

#endif //STOPWATCH_H