#include <windows.h>

#include "timer.h"

struct LDFS_Timer LDFS_Timer;
double LDFS_Framerate = 1.0f / 60.0f * 1000.0f;
float LDFS_FrameStart;

short LDFS_InitTimer(void) {
	memset(&LDFS_Timer, 0, sizeof(LDFS_Timer));
	
	if(!QueryPerformanceFrequency((LARGE_INTEGER *)&LDFS_Timer.frequency)) {
		LDFS_Timer.usingPerformanceTimer = 0;
		LDFS_Timer.multimediaTimerStart = timeGetTime();
		LDFS_Timer.resolution = 1.0f / 1000.0f;
		LDFS_Timer.frequency = 1000;
		LDFS_Timer.multimediaTimerElapsed = LDFS_Timer.multimediaTimerStart;
		return 0;
	}
	else {
		QueryPerformanceCounter((LARGE_INTEGER *) &LDFS_Timer.performanceTimerStart);
		LDFS_Timer.usingPerformanceTimer = 1;
		LDFS_Timer.resolution = (float)(((double)1.0f) / ((double)LDFS_Timer.frequency));
		LDFS_Timer.performanceTimerElapsed = LDFS_Timer.performanceTimerStart;
		return 1;
	}
	
	LDFS_FrameStart = LDFS_GetTime();
}

float LDFS_GetTime(void) {
	__int64 time;
	
	if(LDFS_Timer.usingPerformanceTimer) {
		QueryPerformanceCounter((LARGE_INTEGER *) &time);
		return ((float)(time - LDFS_Timer.performanceTimerStart) * LDFS_Timer.resolution) * 1000.0f;
	}
	else {
		return ((float)(timeGetTime() - LDFS_Timer.multimediaTimerStart) * LDFS_Timer.resolution) * 1000.0f;
	}
}

inline void LDFS_SetFramerate(double framerate) {
	LDFS_Framerate = framerate;
}

void LDFS_MaintainFramerate(void) {
	float t = LDFS_FrameStart + LDFS_Framerate - LDFS_GetTime();
	if(t > 0) Sleep(t);
	
	LDFS_FrameStart = LDFS_GetTime();
}
