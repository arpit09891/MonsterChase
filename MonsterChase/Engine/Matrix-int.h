#pragma once


inline Vector4 operator*(const Matrix & i_mtx, const Vector4 & i_vec)
{
	return Vector4(i_mtx.MultiplyRight(i_vec));
}

inline Vector4 operator*(const Vector4 & i_vec, const Matrix & i_mtx)
{
	return Vector4(i_mtx.MultiplyLeft(i_vec));
}

inline Matrix Matrix::operator*(const Matrix & i_other) const
{
	Matrix o_out;
	Multiply(i_other, o_out);
	return o_out;
}