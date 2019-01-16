#include "Point2D.h"


void Point2D::Normalize()
{
	
	float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y));
	assert(length != 0, "length is zero");
	m_x = m_x / length;
	m_y = m_y / length;
	 
	//Point2D normalizedVector(m_x / length, m_y / length);
	//return normalizedVector;

	/*if (m_x > 0)
		m_x = 1;
	else if (m_x == 0)
		m_x = 0;
	else
		m_x = -1;

	if (m_y == 0)
		m_y = 0;
	else if (m_y > 0)
		m_y = 1;
	else
		m_y = -1;*/
}

Point2D::Point2D(const Point2D & i_other)
{
	m_x = i_other.getX();
	m_y = i_other.getY();
}

Point2D operator+ (const Point2D & i_lhs, const Point2D & i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX()+i_rhs.getX());
	result.setY(i_lhs.getY() + i_rhs.getY());
	return result;
}

Point2D operator+ (const Point2D & i_lhs, const int i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() + i_rhs);
	result.setY(i_lhs.getY() + i_rhs);
	return result;
}

Point2D operator-(const Point2D & i_lhs, const Point2D & i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() - i_rhs.getX());
	result.setY(i_lhs.getY() - i_rhs.getY());
	return result;

}

Point2D operator-(const Point2D & i_lhs, const int i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() - i_rhs);
	result.setY(i_lhs.getY() - i_rhs);
	return result;

}

Point2D operator+=(const Point2D & i_lhs, const Point2D & i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() + i_rhs.getX());
	result.setY(i_lhs.getY() + i_rhs.getY());
	return result;
}

Point2D operator-=(const Point2D & i_lhs, const Point2D & i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() - i_rhs.getX());
	result.setY(i_lhs.getY() - i_rhs.getY());
	return result;

}

Point2D operator/(const Point2D & i_lhs, const int i_rhs)
{
	Point2D result;
	if (i_rhs == 0)
	{
		return Point2D(0,0);
	}
	result.setX(i_lhs.getX() / i_rhs);
	result.setY(i_lhs.getY() / i_rhs);
	return result;
}

Point2D operator*(const Point2D & i_lhs, const float i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() * i_rhs);
	result.setY(i_lhs.getY() * i_rhs);
	return result;
}

Point2D operator*(const Point2D & i_lhs, const Point2D i_rhs)
{
	Point2D result;
	result.setX(i_lhs.getX() * i_rhs.getX());
	result.setY(i_lhs.getY() * i_rhs.getY());
	return result;
}


Point2D operator++(const Point2D & i_lhs)
{
	Point2D result;
	result.setX(i_lhs.getX()+1);
	result.setY(i_lhs.getY()+1);
	return result;
}

Point2D operator--(const Point2D & i_lhs)
{
	Point2D result;
	result.setX(i_lhs.getX() - 1);
	result.setY(i_lhs.getY() - 1);
	return result;
}