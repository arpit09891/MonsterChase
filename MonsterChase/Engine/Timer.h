#pragma once

namespace Timer {

	long long GetFrequency();
	long long GetCounter();
	float CalcLastFrameTime();
	float GetTimeDiff_ms(long long);
};