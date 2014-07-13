#pragma once

struct LDFS_Timer {
	__int64 frequency;
	float resolution;
	unsigned long multimediaTimerStart;
	unsigned long multimediaTimerElapsed;
	short usingPerformanceTimer;
	__int64 performanceTimerStart;
	__int64 performanceTimerElapsed;
};

extern struct LDFS_Timer LDFS_Timer;
extern double LDFS_Framerate;
extern float LDFS_FrameStart;

short LDFS_InitTimer(void);
float LDFS_GetTime(void);
inline void LDFS_SetFramerate(double framerate);
void LDFS_MaintainFramerate(void);
