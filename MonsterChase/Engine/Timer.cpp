#include"Timer.h"
#include<Windows.h>
#include<stdio.h>
#define DESIRED_FPS		60.0f
#define DESIRED_FRAMETIME_MS	1.0f
#define MAX_FRAMETIME_MS	(2 * DESIRED_FRAMETIME_MS)
#define CONSTANT_FRAMETIME 1.0f

float GetLastFrameTime_ms()
{
#if defined( CONSTANT_FRAMETIME )
	return DESIRED_FRAMETIME_MS;
#elif defined( CLAMP_FRAMETIME )
	if (LastFrameTime_ms > MAX_FRAMETIME_MS)
		return MAX_FRAMETIME_MS;
	else
		return LastFrameTime_ms;
#else
	return LastFrameTime_ms;
#endif
}


namespace Timer {
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
	long long g_LastFrameStartTick =0;
}


long long Timer::GetCounter()
{
	LARGE_INTEGER li;	
	QueryPerformanceCounter(&li);
	long long temp = li.QuadPart;
	return long long(li.QuadPart);
}

long long Timer::GetFrequency() {
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	return long long(Frequency.QuadPart);
}

float Timer::CalcLastFrameTime() {
	float g_LastFrameTime_ms = 0;
	long long currentTick = GetCounter();

#if defined( CONSTANT_FRAMETIME )
	return DESIRED_FRAMETIME_MS;
#elif defined( CLAMP_FRAMETIME )
	if (LastFrameTime_ms > MAX_FRAMETIME_MS)
		return MAX_FRAMETIME_MS;
	else
		return LastFrameTime_ms;
#else
	return LastFrameTime_ms;
#endif
	char message[500];
	const size_t	lenBuffer = 100;

	if (g_LastFrameStartTick != 0) {
		long long elapsedTicks = currentTick - g_LastFrameStartTick;
		long long temp = elapsedTicks;
		temp *= 1000000;
		temp /= GetFrequency();
		/*g_LastFrameTime_ms = elapsedTicks;
		g_LastFrameTime_ms *= 1000000;
		g_LastFrameTime_ms /= GetFrequency();*/
		g_LastFrameTime_ms = static_cast<float>(temp);
		g_LastFrameTime_ms /= 1000;
	}
	else
		g_LastFrameTime_ms = 1;

	//Note the start of this frame
	g_LastFrameStartTick = currentTick;
	
	//sprintf_s(message,lenBuffer,"\n The Frame Time %f \n.............", g_LastFrameTime_ms);
	//OutputDebugStringA(message);

	return g_LastFrameTime_ms;
}

float Timer::GetTimeDiff_ms(long long startTime)
{
	long long TimeDiff_ms = GetCounter() - startTime;
	float TimeDiff = static_cast<float>(TimeDiff_ms);
	TimeDiff = TimeDiff * 1000;
	return TimeDiff;
}
