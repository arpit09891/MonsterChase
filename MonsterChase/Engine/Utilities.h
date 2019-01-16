#ifndef __MATH_UTILITIES_H
#define __MATH_UTILITIES_H

#include <stdint.h>

namespace Engine
{
	namespace Math
	{


		inline float 			DegreesToRadians(float i_Degrees);
		inline double 			DegreesToRadians(double i_Degrees);

		inline bool 			IsNAN(float i_val);
		inline bool 			IsZero(float i_val);

		// fastest
		inline bool 			AreEqual_Eps(float i_lhs, float i_rhs, float i_maxDiff = 0.00001f);
		// balanced
		inline bool 			AreEqual_Rel(float i_lhs, float i_rhs, float i_maxDiff = 0.00001f);
		// slow but sure
		inline bool 			AreEqual_Accurate(float i_lhs, float i_rhs, float i_maxDiff, unsigned int i_maxULPS = 12);

		inline unsigned int 	RandInRange(unsigned int i_lowerBound, unsigned int i_upperBound);

		template< typename T>
		inline void				Swap(T & i_Left, T & i_Right);

		static const uint32_t 	allBitsSet = ~0;
		//const float 			NAN = *reinterpret_cast<const float *>(&allBitsSet);

	} // namespace Math
} // namespace Engine

#include "Utilities-inl.h"
#endif // __MATH_UTILITIES_H