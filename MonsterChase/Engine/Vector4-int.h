#include "Vector4.h"
#pragma once


inline Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) :
	m_x(i_x),
	m_y(i_y),
	m_z(i_z),
	w(i_w)
{
	int check = 0;
	//w = 0.0f;
	// lets not create a Vector element with an invalid float
	/*assert(!IsNaN(i_x));
	assert(!IsNaN(i_y));
	assert(!IsNaN(i_z));*/
}

inline Vector4::Vector4(const Vector4 & i_rhs) :
	m_x(i_rhs.m_x),
	m_y(i_rhs.m_y),
	m_z(i_rhs.m_z),
	w(i_rhs.w)
{
	// lets not create a Vector element with an invalid float
	/*assert(!IsNaN(i_rhs.m_x));
	assert(!IsNaN(i_rhs.m_y));
	assert(!IsNaN(i_rhs.m_z));*/
}

inline Vector4::Vector4(const Vector3 & i_rhs, float w):
	m_x(i_rhs.GetX()),
	m_y(i_rhs.GetY()),
	m_z(i_rhs.GetZ()),
	w(w)
{
}

inline float Vector4::GetX(void) const
{
	return m_x;
}

inline float Vector4::GetY(void) const
{
	return m_y;
}

inline float Vector4::GetZ(void) const
{
	return m_z;
}

inline float Vector4::GetW(void) const
{
	return w;
}

inline void Vector4::SetX(float i_x)
{
	assert(!IsNaN(i_x));

	m_x = i_x;
}

inline void Vector4::SetY(float i_y)
{
	assert(!IsNaN(i_y));

	m_y = i_y;
}

inline void Vector4::SetZ(float i_z)
{
	assert(!IsNaN(i_z));

	m_z = i_z;
}

inline const Vector4 & Vector4::operator=(const Vector4 & i_rhs)
{
	assert(!IsNaN(i_rhs.m_x));
	assert(!IsNaN(i_rhs.m_y));
	assert(!IsNaN(i_rhs.m_z));

	m_x = i_rhs.m_x;
	m_y = i_rhs.m_y;
	m_z = i_rhs.m_z;
	w = i_rhs.w;

	return *this;
}



