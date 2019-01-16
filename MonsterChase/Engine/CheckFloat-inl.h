#pragma once
#include<math.h>



inline bool IsNaN(float i_value)
{
	volatile float val = i_value;
	return val != val;
}

inline bool AreAboutEqual(float i_lhs, float i_rhs, float epsilon = .0001f)
{

	return fabs(i_rhs - i_lhs) < epsilon;
}

inline bool IsZero(float i_val)
{
	return AreAboutEqual(i_val, .000000001f);
}

