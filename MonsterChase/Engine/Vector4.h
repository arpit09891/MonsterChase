#pragma once
#include"Vector3.h"
class Vector4 {
	float	m_x, m_y, m_z, w;

public:
	// default constructor - good for calling new Vector3[];
	Vector4()				// we define the body here. this is the same as making it an inline.
							// in an optimized build it should be a no-op.
	{
	}

	// copy constructor - for completeness
	
	// standard constructor
	inline Vector4(float i_x, float i_y, float i_z,float w);

	// copy constructor - for completeness
	inline Vector4(const Vector4 & i_rhs);
	inline Vector4(const Vector3 & i_rhs, float w = 1.0f);

	// element accessors
	// - get individual element
	float GetX(void) const;
	float GetY(void) const;
	float GetZ(void) const;
	float GetW(void) const;
	// - set individual element
	void SetX(float i_x);
	void SetY(float i_y);
	void SetZ(float i_z);

	inline const Vector4 & operator=(const Vector4 & i_rhs);
};

#include"Vector4-int.h"