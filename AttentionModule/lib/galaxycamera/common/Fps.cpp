//--------------------------------------------------------------------------------
/**
\file     Fps.h
\brief    CFps class implementation
*/
//----------------------------------------------------------------------------------
#include "StdAfx.h"
#include "Fps.h"


//----------------------------------------------------------------------------------
/**
\brief  Construction
*/
//----------------------------------------------------------------------------------

CFps::CFps(void)
:m_nFrameCount(0)
,m_dBeginTime(0)
,m_dEndTime(0)
,m_nTotalFrameCount(0)
,m_dFps(0)
{
    //Start the timer
    m_objStopWatch.Start();
}

//----------------------------------------------------------------------------------
/**
\brief  Destruction
*/
//----------------------------------------------------------------------------------

CFps::~CFps(void)
{
}

//----------------------------------------------------------------------------------
/**
\brief  Get the latest frame rate

\return frame rate
*/
//----------------------------------------------------------------------------------
double CFps::GetFps(void) 
{
    return m_dFps;
} 


//----------------------------------------------------------------------------------
/**
\brief  Increase the number of frames
*/
//----------------------------------------------------------------------------------

void CFps::IncreaseFrameNum(void)
{
    //Increase total the number of frames
    m_nTotalFrameCount++;

    //Increase the number of frames
    m_nFrameCount++;

    //The update interval
    m_dEndTime = m_objStopWatch.Stop();
}


//----------------------------------------------------------------------------------
/**
\brief  Update frame rate
*/
//----------------------------------------------------------------------------------
void CFps::UpdateFps(void)
{   
    double dInterval = m_dEndTime - m_dBeginTime;

	// Check whether the time interval equals zero
    if(dInterval > 0) 
    {
        m_dFps = 1000.0 * m_nFrameCount / dInterval;
        m_nFrameCount   = 0;                            //The accumulated frames are cleared
        m_dBeginTime   = m_dEndTime;                    //Update start time
    }
    else if(dInterval == 0)
    {
        m_dFps = 0;
    }
    else{}

}