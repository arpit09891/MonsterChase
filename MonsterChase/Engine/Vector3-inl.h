#include <assert.h>
#include"CheckFloat-inl.h"
#include "Utilities.h"
#include <xmmintrin.h>  
#include<smmintrin.h>

		inline Vector3::Vector3(float i_x, float i_y, float i_z) :
			m_x(i_x),
			m_y(i_y),
			m_z(i_z)
		{
			// lets not create a Vector element with an invalid float
			/*assert(!IsNaN(i_x));
			assert(!IsNaN(i_y));
			assert(!IsNaN(i_z));*/
		}

		inline Vector3::Vector3(const Vector3 & i_rhs) :
			m_x(i_rhs.m_x),
			m_y(i_rhs.m_y),
			m_z(i_rhs.m_z)
		{
			// lets not create a Vector element with an invalid float
			/*assert(!IsNaN(i_rhs.m_x));
			assert(!IsNaN(i_rhs.m_y));
			assert(!IsNaN(i_rhs.m_z));*/
		}

		// operators
		inline const Vector3 & Vector3::operator=(const Vector3 & i_rhs)
		{
			/*assert(!IsNaN(i_rhs.m_x));
			assert(!IsNaN(i_rhs.m_y));
			assert(!IsNaN(i_rhs.m_z));*/

			m_x = i_rhs.m_x;
			m_y = i_rhs.m_y;
			m_z = i_rhs.m_z;

			return *this;
		}

		// accessors
		inline float Vector3::GetX(void) const
		{
			return m_x;
		}

		inline float Vector3::GetY(void) const
		{
			return m_y;
		}

		inline float Vector3::GetZ(void) const
		{
			return m_z;
		}

		inline void Vector3::SetX(float i_x)
		{
			assert(!IsNaN(i_x));

			m_x = i_x;
		}

		inline void Vector3::SetY(float i_y)
		{
			assert(!IsNaN(i_y));

			m_y = i_y;
		}

		inline void Vector3::SetZ(float i_z)
		{
			assert(!IsNaN(i_z));

			m_z = i_z;
		}

		inline const Vector3 & Vector3::operator+=(const Vector3 & i_rhs)
		{
			m_x += i_rhs.m_x;
			m_y += i_rhs.m_y;
			m_z += i_rhs.m_z;

			return *this;
		}

		inline const Vector3 & Vector3::operator-=(const Vector3 & i_rhs)
		{
			m_x -= i_rhs.m_x;
			m_y -= i_rhs.m_y;
			m_z -= i_rhs.m_z;

			return *this;
		}

		inline const Vector3 & Vector3::operator*=(float i_rhs)
		{
			assert(!IsNaN(i_rhs));

			m_x *= i_rhs;
			m_y *= i_rhs;
			m_z *= i_rhs;

			return *this;
		}

		inline const Vector3 & Vector3::operator/=(float i_rhs)
		{
			assert(!IsNaN(i_rhs));
			assert(!IsZero(i_rhs));

			m_x /= i_rhs;
			m_y /= i_rhs;
			m_z /= i_rhs;

			return *this;
		}

		inline const Vector3 & Vector3::operator-(void)
		{
			return Vector3(-m_x, -m_y, -m_z);
		}

		// stand alone operators
		inline Vector3 operator+(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return Vector3(i_lhs.GetX() + i_rhs.GetX(), i_lhs.GetY() + i_rhs.GetY(), i_lhs.GetZ() + i_rhs.GetZ());
		}

		inline Vector3 operator-(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return Vector3(i_lhs.GetX() - i_rhs.GetX(), i_lhs.GetY() - i_rhs.GetY(), i_lhs.GetZ() - i_rhs.GetZ());
		}

		inline Vector3 operator*(const Vector3 & i_lhs, float i_rhs)
		{
			assert(!IsNaN(i_rhs));

			return Vector3(i_lhs.GetX() * i_rhs, i_lhs.GetY() * i_rhs, i_lhs.GetZ() * i_rhs);
		}

		inline Vector3 operator*(float i_lhs, const Vector3 & i_rhs)
		{
			assert(!IsNaN(i_lhs));

			return Vector3(i_rhs.GetX() * i_lhs, i_rhs.GetY() * i_lhs, i_rhs.GetZ() * i_lhs);
		}

		inline Vector3 operator*(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			
			return Vector3(i_rhs.GetX() * i_lhs.GetX(), i_rhs.GetY() * i_lhs.GetY(), i_rhs.GetZ() * i_lhs.GetZ());
		}

		inline Vector3 operator/(const Vector3 & i_lhs, float i_rhs)
		{
			assert(!IsNaN(i_rhs));
			assert(!IsZero(i_rhs));

			return Vector3(i_lhs.GetX() / i_rhs, i_lhs.GetY() / i_rhs, i_lhs.GetZ() / i_rhs);
		}
		
		inline bool operator==(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return AreAboutEqual(i_lhs.GetX(), i_rhs.GetX()) && AreAboutEqual(i_lhs.GetY(), i_rhs.GetY()) && AreAboutEqual(i_lhs.GetZ(), i_rhs.GetZ());
		}

		inline bool operator!=(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return !AreAboutEqual(i_lhs.GetX(), i_rhs.GetX()) || !AreAboutEqual(i_lhs.GetY(), i_rhs.GetY()) || !AreAboutEqual(i_lhs.GetZ(), i_rhs.GetZ());
		}

		inline float dot(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			__m128 vec0 = { i_lhs.GetX(), i_lhs.GetY(), i_lhs.GetZ(), 0.0f };
			__m128 vec1 = { i_rhs.GetX(), i_rhs.GetY(), i_rhs.GetZ(), 0.0f };
			
			__m128 vec2 = _mm_dp_ps(vec0, vec1, 0X71);
			float dot = _mm_cvtss_f32(vec2);
			return dot;
		}

		/*inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return Vector3(i_lhs.GetY() * i_rhs.GetZ() - i_lhs.GetZ() * i_rhs.GetY(),
				i_lhs.GetZ() * i_rhs.GetX() - i_lhs.GetX() * i_rhs.GetZ(),
				i_lhs.GetX() * i_rhs.GetY() - i_lhs.GetY() * i_rhs.GetX());
		}*/
		inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs)
		{
			return Vector3(_mm_sub_ps(
				_mm_mul_ps(_mm_shuffle_ps(i_lhs.GetM_vec(), i_lhs.GetM_vec(), _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(i_rhs.GetM_vec(), i_rhs.GetM_vec(), _MM_SHUFFLE(3, 1, 0, 2))),

				_mm_mul_ps(_mm_shuffle_ps(i_lhs.GetM_vec(), i_lhs.GetM_vec(), _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(i_rhs.GetM_vec(), i_rhs.GetM_vec(), _MM_SHUFFLE(3, 0, 2, 1)))
			));
		}


