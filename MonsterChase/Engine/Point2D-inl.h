#pragma once
#include"Debug.h"
#include <math.h>
#include"CheckFloat-inl.h"


#include<stdio.h>

inline bool operator==(const Point2D & i_lhs, Point2D i_rhs) {
	
	
	if (AreAboutEqual(i_lhs.getX(), i_rhs.getX()) && AreAboutEqual(i_lhs.getY(), i_rhs.getY()))
		return true;
	else
		return false;

}

inline bool operator!=(const Point2D & i_lhs, Point2D i_rhs) {
	if (!AreAboutEqual(i_lhs.getX(), i_rhs.getX()) || !AreAboutEqual(i_lhs.getY(), i_rhs.getY()))
		return true;
	else
		return false;

}
inline void Point2D::setX(const float i_x) 
{
	assert(!IsNaN(i_x), "This is not a number ");
	m_x = i_x; 
}

inline void Point2D::setY(const float i_y) 
{ 
	assert(!IsNaN(i_y), "This is not a number ");
	m_y = i_y; 
}