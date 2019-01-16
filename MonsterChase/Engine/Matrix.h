#pragma once
#include"Vector4.h"
#include<stdint.h>

class Matrix {
public:
	Matrix();
	Matrix(float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44);
	Matrix(const Matrix & i_other);
	
	Matrix &operator = (const Matrix &i_other);
	static Matrix CreateIdentity(void);
	
	static Matrix CreateXRotation(float i_rotationRadians);
	static Matrix CreateYRotation(float i_rotationRadians);
	static Matrix CreateZRotation(float i_rotationRadians);

	static Matrix CreateTransaltion(Vector3 & i_translation);
	static Matrix CreateTransaltion(float i_transX, float i_transY, float i_transZ);
	static Matrix CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ);
	
	void Invert(void);
	Matrix GetInverse(void)	const;
	
	void Transpose(void);
	Matrix GetTranspose(void);
	Matrix GetTranspose(void) const;

	Matrix Multiply(const Matrix &i_other, Matrix &o_out)	const;
	inline Matrix operator*(const Matrix &i_other)const;
	
	//has to change them into vector4
	Vector4 MultiplyLeft(const Vector4 & i_other)const;
	Vector4 MultiplyRight(const Vector4 &i_other)const;
private:
	float m_11, m_12, m_13, m_14,
		m_21, m_22, m_23, m_24,
		m_31, m_32, m_33, m_34,
		m_41, m_42, m_43, m_44 ;

	const uint32_t allBitsSet = ~0;
	//const float NAN = *	reinterpret_cast<const float *>(&allBitsSet);
};

inline Vector4 operator*(const Matrix &i_mtx, const Vector4 &i_vec);
inline Vector4 operator*(const Vector4 &i_vec, const Matrix &i_mtx);

#include"Matrix-int.h"