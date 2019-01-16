#include "Matrix.h"
#include"Vector3.h"
#include"CheckFloat-inl.h"
#include<math.h>

Matrix::Matrix()
{
#ifdef _DEBUG
	//m_11 = Azra::NAN;
#endif // _DEBUG

}

Matrix::Matrix(float i_11, float i_12, float i_13, float i_14, 
	float i_21, float i_22, float i_23, float i_24, 
	float i_31, float i_32, float i_33, float i_34, 
	float i_41, float i_42, float i_43, float i_44)
	:
	m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
	m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
	m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
	m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
{

}

Matrix::Matrix(const Matrix & i_other)
	:
	m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
	m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_24),
	m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_34),
	m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44)
{
}

Matrix & Matrix::operator=(const Matrix & i_other)
{
	m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
	m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
	m_31 = i_other.m_31; m_32 = i_other.m_32; m_13 = i_other.m_33; m_14 = i_other.m_34;
	m_41 = i_other.m_41; m_42 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;

	return *this;
}

Matrix Matrix::CreateIdentity(void)
{
	return Matrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::CreateXRotation(float i_rotationRadians)
{
	float sin = sinf(i_rotationRadians);
	float cos = cosf(i_rotationRadians);
	return Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos, sin, 0.0f,
		0.0f, -sin, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::CreateYRotation(float i_rotationRadians)
{
	float sin = sinf(i_rotationRadians);
	float cos = cosf(i_rotationRadians);
	return Matrix(
		cos, 0.0f, -sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin, 0.0f, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::CreateZRotation(float i_rotationRadians)
{
	float sin = sinf(i_rotationRadians);
	float cos = cosf(i_rotationRadians);
	return Matrix(
		cos, sin, 0.0f, 0.0f,
		-sin, cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::CreateTransaltion(Vector3 & i_translation)
{
	return Matrix(
		1.0f, 0.0f, 0.0f, i_translation.GetX(),
		0.0f, 1.0f, 0.0f, i_translation.GetY(),
		0.0f, 0.0f, 1.0f, i_translation.GetZ(),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::CreateTransaltion(float i_transX, float i_transY, float i_transZ)
{
	return Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		i_transX, i_transY, i_transZ, 1.0f
	);
}

Matrix Matrix::CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ)
{
	return Matrix(
		i_ScaleX, 0.0f, 0.0f, 0.0f,
		0.0f, i_ScaleY, 0.0f, 0.0f,
		0.0f, 0.0f, i_ScaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Matrix::Invert(void)
{
	*this = GetInverse();
}

Matrix Matrix::GetInverse(void) const
{
	float m[16];

	m[0] = m_11; m[1] = m_12; m[2] = m_13; m[3] = m_14;
	m[4] = m_21; m[5] = m_22; m[6] = m_23; m[7] = m_24;
	m[8] = m_31; m[9] = m_32; m[10] = m_33; m[11] = m_34;
	m[12] = m_41; m[13] = m_42; m[14] = m_43; m[15] = m_44;

	double inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	det = 1.0 / det;
	float invOut[16];
	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return Matrix(invOut[0], invOut[1], invOut[2], invOut[3],
			invOut[4], invOut[5], invOut[6], invOut[7],
			invOut[8], invOut[9], invOut[10], invOut[11],
			invOut[12], invOut[13], invOut[14], invOut[15]
			);
}

void Matrix::Transpose(void)
{
	// assert(!isnan(m_11));

	register float temp;

	temp = m_21; m_21 = m_12; m_12 = temp;
	temp = m_31; m_31 = m_13; m_13 = temp;
	temp = m_41; m_41 = m_14; m_14 = temp;

	temp = m_32; m_32 = m_23; m_23 = temp;
	temp = m_42; m_42 = m_24; m_24 = temp;

	temp = m_43; m_43 = m_34; m_34 = temp;
}

Matrix Matrix::GetTranspose(void)
{
	// assert(!isnan(m_11));
	return Matrix(
			m_11, m_21, m_31, m_41,
			m_12, m_22, m_32, m_42,
			m_13, m_23, m_33, m_43,
			m_14, m_24, m_34, m_44
	);
}

Matrix Matrix::GetTranspose(void) const
{
	// assert(!isnan(m_11));
	return Matrix(
		m_11, m_21, m_31, m_41,
		m_12, m_22, m_32, m_42,
		m_13, m_23, m_33, m_43,
		m_14, m_24, m_34, m_44
	);
}

Matrix Matrix::Multiply(const Matrix & i_other, Matrix & o_out) const
{
	//assert(IsNaN(m_11));
	__m128 row1 = { m_11, m_12, m_13, m_14 };
	__m128 row2 = { m_21, m_22, m_23, m_24 };
	__m128 row3 = { m_31, m_32, m_33, m_34 };
	__m128 row4 = { m_41, m_42, m_43, m_44 };

	__m128 col1 = { i_other.m_11, i_other.m_21, i_other.m_31, i_other.m_41 };
	__m128 col2 = { i_other.m_12, i_other.m_22, i_other.m_32, i_other.m_42 };
	__m128 col3 = { i_other.m_13, i_other.m_23, i_other.m_33, i_other.m_43 };
	__m128 col4 = { i_other.m_14, i_other.m_24, i_other.m_34, i_other.m_44 };

	__m128 dotProduct = _mm_dp_ps(row1, col1, 0Xff);
	o_out.m_11 = _mm_cvtss_f32(dotProduct);
	
	dotProduct = _mm_dp_ps(row1, col2, 0Xff);
	o_out.m_12 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row1, col3, 0Xff);
	o_out.m_13 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row1, col4, 0Xff);
	o_out.m_14 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row2, col1, 0Xff);
	o_out.m_21 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row2, col2, 0Xff);
	o_out.m_22 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row2, col3, 0Xff);
	o_out.m_23 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row2, col4, 0Xff);
	o_out.m_24 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row3, col1, 0Xff);
	o_out.m_31 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row3, col2, 0Xff);
	o_out.m_32 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row3, col3, 0Xff);
	o_out.m_33 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row3, col4, 0Xff);
	o_out.m_34 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row4, col1, 0Xff);
	o_out.m_41 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row4, col2, 0Xff);
	o_out.m_42 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row4, col3, 0Xff);
	o_out.m_43 = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(row4, col4, 0Xff);
	o_out.m_44 = _mm_cvtss_f32(dotProduct);


	/*o_out.m_11 = m_11 * i_other.m_11 + m_12 * i_other.m_21 + m_13 * i_other.m_31 + m_14 * i_other.m_41;
	o_out.m_12 = m_11 * i_other.m_12 + m_12 * i_other.m_22 + m_13 * i_other.m_32 + m_14 * i_other.m_42;
	o_out.m_13 = m_11 * i_other.m_13 + m_12 * i_other.m_23 + m_13 * i_other.m_33 + m_14 * i_other.m_43;
	o_out.m_14 = m_11 * i_other.m_14 + m_12 * i_other.m_24 + m_13 * i_other.m_34 + m_14 * i_other.m_44;

	o_out.m_21 = m_21 * i_other.m_11 + m_22 * i_other.m_21 + m_23 * i_other.m_31 + m_24 * i_other.m_41;
	o_out.m_22 = m_21 * i_other.m_12 + m_22 * i_other.m_22 + m_23 * i_other.m_32 + m_24 * i_other.m_42;
	o_out.m_23 = m_21 * i_other.m_13 + m_22 * i_other.m_23 + m_23 * i_other.m_33 + m_24 * i_other.m_43;
	o_out.m_24 = m_21 * i_other.m_14 + m_22 * i_other.m_24 + m_23 * i_other.m_34 + m_24 * i_other.m_44;

	o_out.m_31 = m_31 * i_other.m_11 + m_32 * i_other.m_21 + m_33 * i_other.m_31 + m_34 * i_other.m_41;
	o_out.m_32 = m_31 * i_other.m_12 + m_32 * i_other.m_22 + m_33 * i_other.m_32 + m_34 * i_other.m_42;
	o_out.m_33 = m_31 * i_other.m_13 + m_32 * i_other.m_23 + m_33 * i_other.m_33 + m_34 * i_other.m_43;
	o_out.m_34 = m_31 * i_other.m_14 + m_32 * i_other.m_24 + m_33 * i_other.m_34 + m_34 * i_other.m_44;

	o_out.m_41 = m_41 * i_other.m_11 + m_42 * i_other.m_21 + m_43 * i_other.m_31 + m_44 * i_other.m_41;
	o_out.m_42 = m_41 * i_other.m_12 + m_42 * i_other.m_22 + m_43 * i_other.m_32 + m_44 * i_other.m_42;
	o_out.m_43 = m_41 * i_other.m_13 + m_42 * i_other.m_23 + m_43 * i_other.m_33 + m_44 * i_other.m_43;
	o_out.m_44 = m_41 * i_other.m_14 + m_42 * i_other.m_24 + m_43 * i_other.m_34 + m_44 * i_other.m_44;
*/
	return o_out;
}

Vector4 Matrix::MultiplyLeft(const Vector4 & i_Vector) const
{
	__m128 vec0 = { i_Vector.GetX(), i_Vector.GetY(), i_Vector.GetZ(), i_Vector.GetW() };
	__m128 vec1 = { m_11, m_21, m_31, m_41 };
	__m128 vec2 = { m_12, m_22, m_32, m_42 };
	__m128 vec3 = { m_13, m_23, m_33, m_43 };
	__m128 vec4 = { m_14, m_24, m_34, m_44 };

	__m128 dotProduct = _mm_dp_ps(vec0, vec1, 0Xff);
	float x = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec2, 0Xff);
	float y = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec3, 0Xff);
	float z = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec4, 0Xff);
	float w = _mm_cvtss_f32(dotProduct);
	

	return Vector4(x, y, z, w);
}

Vector4 Matrix::MultiplyRight(const Vector4 & i_Vector) const
{
	__m128 vec0 = { i_Vector.GetX(), i_Vector.GetY(), i_Vector.GetZ(), i_Vector.GetW() };
	__m128 vec1 = { m_11, m_12, m_13, m_14 };
	__m128 vec2 = { m_21, m_22, m_23, m_24 };
	__m128 vec3 = { m_31, m_32, m_33, m_34 };
	__m128 vec4 = { m_41, m_42, m_43, m_44 };

	__m128 dotProduct = _mm_dp_ps(vec0, vec1, 0Xff);
	float x = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec2, 0Xff);
	float y = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec3, 0Xff);
	float z = _mm_cvtss_f32(dotProduct);

	dotProduct = _mm_dp_ps(vec0, vec4, 0Xff);
	float w = _mm_cvtss_f32(dotProduct);

	return Vector4(x, y, z, w);
}
