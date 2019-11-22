//--------------------------------------------------------------------------------
/**
\file     Fps.h
\brief    CFps calss declaration
*/
//----------------------------------------------------------------------------------

#ifndef FPS_H
#define FPS_H

#include "StopWatch.h"

//--------------------------------------------------------------------------------
/**
\file     CFps class will be used to calculate the frame rate
			
		  CFps is thread safe
*/
//----------------------------------------------------------------------------------

class CFps
{
public:

	///Construction
	CFps(void);

	///Destruction
	~CFps(void);	

    ///Get the latest frame rate
    double GetFps(void);

    ///Get the total number of frames
    inline size_t GetTotalFrameCount(void); 

	///Increase the number of frames
	void IncreaseFrameNum(void);

    ///Update frame rate
    void UpdateFps(void);

    ///Restore the timer to an initial state
    inline void Reset(void);

private:
	size_t    m_nFrameCount;        ///< The number of frames accumulated since the last calculation

    double    m_dBeginTime;         ///< A frame of time before the first frame(Initial 0)
    double    m_dEndTime;           ///< Last frame time

	double    m_dFps;               ///< The last frame rate(frame/second)
	size_t    m_nTotalFrameCount;   ///< The cumulative number of frames


	CStopWatch m_objStopWatch;            ///< timer
};

//----------------------------------------------------------------------------------
/**
\brief Get the latest frame rate
\return  the total number of  frames
*/
//----------------------------------------------------------------------------------
inline size_t CFps::GetTotalFrameCount(void) 
{
    return m_nTotalFrameCount;
} 



//----------------------------------------------------------------------------------
/**
\brief  Restore the timer to an initial state
*/
//----------------------------------------------------------------------------------

inline void CFps::Reset(void)
{
    m_nFrameCount       = 0;
    m_dBeginTime        = 0;
    m_dEndTime          = 0;
    m_nTotalFrameCount  = 0;
    m_dFps              = 0;
}




#endif //FPS_H