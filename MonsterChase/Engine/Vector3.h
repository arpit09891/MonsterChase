#pragma once
#include<xmmintrin.h>

union Vector3
{
private:
	struct {
		float	m_x, m_y, m_z;
	};
	__m128 m_vec;
	
public:
	
	// default constructor - good for calling new Vector3[];
	Vector3()				// we define the body here. this is the same as making it an inline.
							// in an optimized build it should be a no-op.
	{
		m_x = 0.0f;
		m_y = 0.0f;
		m_z = 0.0f;
	}

	// standard constructor
	inline Vector3(float i_x, float i_y, float i_z);

	Vector3(const __m128 i_vec) :
		m_vec(i_vec)
	{}

	__m128 GetM_vec() const { return m_vec; }
	// copy constructor - for completeness
	inline Vector3(const Vector3 & i_rhs);

	// assignment operator
	inline const Vector3 & operator=(const Vector3 & i_rhs);

	// element accessors
	// - get individual element
	float GetX(void) const;
	float GetY(void) const;
	float GetZ(void) const;
	// - set individual element
	void SetX(float i_x);
	void SetY(float i_y);
	void SetZ(float i_z);

	const Vector3 & operator+=(const Vector3 & i_rhs);
	const Vector3 & operator-=(const Vector3 & i_rhs);

	const Vector3 & operator*=(float i_val);
	const Vector3 & operator/=(float i_val);

	// negate
	const Vector3 & operator-(void);

	// - ( 0.0f, 0.0f, 0.0f )
	static const Vector3 Zero;
};

inline Vector3 operator+(const Vector3 & i_lhs, const Vector3 & i_rhs);
inline Vector3 operator-(const Vector3 & i_lhs, const Vector3 & i_rhs);

inline Vector3 operator*(const Vector3 & i_lhs, float i_rhs);
inline Vector3 operator*(float i_lhs, const Vector3 & i_rhs);
inline Vector3 operator*(const Vector3 & i_lhs, const Vector3 & i_rhs);
inline Vector3 operator/(const Vector3 & i_lhs, float i_rhs);

inline bool operator==(const Vector3 & i_lhs, const Vector3 & i_rhs);
inline bool operator!=(const Vector3 & i_lhs, const Vector3 & i_rhs);

inline float dot(const Vector3 & i_lhs, const Vector3 & i_rhs);
inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs);

#include "Vector3-inl.h"
