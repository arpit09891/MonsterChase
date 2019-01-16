#pragma once

class Point2D
{
public:

	Point2D()
	{
	};

	Point2D(float i_x, float i_y) :
		m_x(i_x),
		m_y(i_y)
	{

	}
	Point2D(const Point2D & i_other);
	//get
	inline float getX() const 
	{ return  m_x ; }
	inline float getY() const { return m_y; }
	//set
	inline void setX(const float i_x);
	inline void setY(const float i_y);
	void Normalize();
	
private:
		float	m_x = 0, m_y = 0;
};

Point2D operator+(const Point2D & i_lhs, const Point2D & i_rhs);
Point2D operator+(const Point2D & i_lhs, const int i_rhs);
Point2D operator-(const Point2D & i_lhs, const Point2D & i_rhs);
Point2D operator-(const Point2D & i_lhs, const int i_rhs);
Point2D operator*(const Point2D & i_lhs, const float i_rhs);
Point2D operator*(const Point2D & i_lhs, const Point2D i_rhs);

Point2D operator/(const Point2D & i_lhs, const int i_rhs);
Point2D operator+=(const Point2D & i_lhs, const Point2D & i_rhs);
Point2D operator-=(const Point2D & i_lhs, const Point2D & i_rhs);
inline bool operator==(const Point2D & i_lhs, const Point2D i_rhs);
inline bool operator!=(const Point2D & i_lhs, const Point2D i_rhs);
Point2D operator++(const Point2D & i_lhs);
Point2D operator--(const Point2D & i_lhs);

#include"Point2D-inl.h"
