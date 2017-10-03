#include "stdafx.h"

#include "Matrix4f.h"

namespace EasyMath
{

	Matrix4f::Matrix4f()
	{
		m_Data[0][0] = 0.0f; m_Data[0][1] = 0.0f; m_Data[0][2] = 0.0f; m_Data[0][3] = 0.0f;
		m_Data[1][0] = 0.0f; m_Data[1][1] = 0.0f; m_Data[1][2] = 0.0f; m_Data[1][3] = 0.0f;
		m_Data[2][0] = 0.0f; m_Data[2][1] = 0.0f; m_Data[2][2] = 0.0f; m_Data[2][3] = 0.0f;
		m_Data[3][0] = 0.0f; m_Data[3][1] = 0.0f; m_Data[3][2] = 0.0f; m_Data[3][3] = 0.0f;
	}

	Matrix4f::Matrix4f(
		float A11, float A12, float A13, float A14,
		float A21, float A22, float A23, float A24,
		float A31, float A32, float A33, float A34,
		float A41, float A42, float A43, float A44
	)
	{
		m_Data[0][0] = A11; m_Data[0][1] = A12; m_Data[0][2] = A13; m_Data[0][3] = A14;
		m_Data[1][0] = A21; m_Data[1][1] = A22; m_Data[1][2] = A23; m_Data[1][3] = A24;
		m_Data[2][0] = A31; m_Data[2][1] = A32; m_Data[2][2] = A33; m_Data[2][3] = A34;
		m_Data[3][0] = A41; m_Data[3][1] = A42; m_Data[3][2] = A43; m_Data[3][3] = A44;
	}

	Matrix4f::Matrix4f(const Matrix4f& Other)
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				m_Data[Row][Column] = Other.m_Data[Row][Column];
			}
		}
	}

	Matrix4f operator + (const Matrix4f& Matrix, float Scale)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = Matrix.m_Data[Row][Column] + Scale;
			}
		}
		return Ret;
	}

	Matrix4f operator - (const Matrix4f& Matrix, float Scale)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = Matrix.m_Data[Row][Column] - Scale;
			}
		}
		return Ret;
	}

	Matrix4f operator * (const Matrix4f& Matrix, float Scale)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = Matrix.m_Data[Row][Column] * Scale;
			}
		}
		return Ret;
	}

	Matrix4f operator * (float Scale, const Matrix4f& Matrix)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = Matrix.m_Data[Row][Column] * Scale;
			}
		}
		return Ret;
	}

	Matrix4f operator / (const Matrix4f& Matrix, float Scale)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = Matrix.m_Data[Row][Column] / Scale;
			}
		}
		return Ret;
	}

	std::ostream& operator << (std::ostream& Out, const Matrix4f& Matrix)
	{
		Out << "Matrix4f" << std::endl;
		Out << Matrix.m_Data[0][0] << '\t' << Matrix.m_Data[0][1] << '\t' << Matrix.m_Data[0][2] << '\t' << Matrix.m_Data[0][3] << std::endl;
		Out << Matrix.m_Data[1][0] << '\t' << Matrix.m_Data[1][1] << '\t' << Matrix.m_Data[1][2] << '\t' << Matrix.m_Data[1][3] << std::endl;
		Out << Matrix.m_Data[2][0] << '\t' << Matrix.m_Data[2][1] << '\t' << Matrix.m_Data[2][2] << '\t' << Matrix.m_Data[2][3] << std::endl;
		Out << Matrix.m_Data[3][0] << '\t' << Matrix.m_Data[3][1] << '\t' << Matrix.m_Data[3][2] << '\t' << Matrix.m_Data[3][3] << std::endl;
		return Out;
	}

	std::istream& operator >> (std::istream& In, Matrix4f& Matrix)
	{
		In >> Matrix.m_Data[0][0] >> Matrix.m_Data[0][1] >> Matrix.m_Data[0][2] >> Matrix.m_Data[0][3];
		In >> Matrix.m_Data[1][0] >> Matrix.m_Data[1][1] >> Matrix.m_Data[1][2] >> Matrix.m_Data[1][3];
		In >> Matrix.m_Data[2][0] >> Matrix.m_Data[2][1] >> Matrix.m_Data[2][2] >> Matrix.m_Data[2][3];
		In >> Matrix.m_Data[3][0] >> Matrix.m_Data[3][1] >> Matrix.m_Data[3][2] >> Matrix.m_Data[3][3];
		return In;
	}

	float Matrix4f::operator () (int32 Row, int32 Column) const
	{
		if (Row < 0 || Row > 3 || Column < 0 || Column > 3)
		{
			DEBUG_ERROR("Row Or Column Is Greater Than 4");
		}

		return m_Data[Row][Column];
	}

	float& Matrix4f::operator () (int32 Row, int32 Column)
	{
		if (Row < 0 || Row > 3 || Column < 0 || Column > 3)
		{
			DEBUG_ERROR("Row Or Column Is Greater Than 4");
		}

		return m_Data[Row][Column];
	}

	bool Matrix4f::operator == (const Matrix4f& Other) const
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				if (m_Data[Row][Column] != Other.m_Data[Row][Column])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool Matrix4f::operator!=(const Matrix4f& Other) const
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				if (m_Data[Row][Column] != Other.m_Data[Row][Column])
				{
					return true;
				}
			}
		}
		return false;
	}

	Matrix4f Matrix4f::operator * (const Matrix4f & Matrix)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] =
					m_Data[Row][0] * Matrix.m_Data[0][Column] +
					m_Data[Row][1] * Matrix.m_Data[1][Column] +
					m_Data[Row][2] * Matrix.m_Data[2][Column] +
					m_Data[Row][3] * Matrix.m_Data[3][Column];
			}
		}
		return Ret;
	}

	Matrix4f& Matrix4f::operator = (const Matrix4f& Other)
	{
		if (this != &Other)
		{
			for (auto Row = 0; Row < 4; Row++)
			{
				for (auto Column = 0; Column < 4; Column++)
				{
					m_Data[Row][Column] = Other.m_Data[Row][Column];
				}
			}
		}
		return *this;
	}

	Matrix4f& Matrix4f::operator += (const Matrix4f& Matrix)
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				m_Data[Row][Column] += Matrix.m_Data[Row][Column];
			}
		}
		return *this;
	}

	Matrix4f& Matrix4f::operator -= (const Matrix4f& Matrix)
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				m_Data[Row][Column] -= Matrix.m_Data[Row][Column];
			}
		}
		return *this;
	}

	Matrix4f& Matrix4f::operator *= (const Matrix4f& Matrix)
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				m_Data[Row][Column] *= Matrix.m_Data[Row][Column];
			}
		}
		return *this;
	}

	Matrix4f& Matrix4f::operator *= (float Scale)
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				m_Data[Row][Column] *= Scale;
			}
		}
		return *this;
	}

	Matrix4f Matrix4f::operator - () const
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = m_Data[Row][Column] * -1.0f;
			}
		}
		return Ret;
	}

	void Matrix4f::SetIdentity()
	{
		memset(m_Data, 0, 25 * sizeof(float));
		for (auto Row = 0; Row < 4; Row++)
		{
			m_Data[Row][Row] = 1.0f;
		}
	}

	void Matrix4f::SetZero()
	{
		memset(m_Data, 0, 25 * sizeof(float));
	}

	void Matrix4f::Trim()
	{
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				if (m_Data[Row][Column] < EPSILON_FLOAT && m_Data[Row][Column] > -EPSILON_FLOAT)
				{
					m_Data[Row][Column] = 0.0f;
				}
			}
		}
	}

	Matrix4f Matrix4f::Inverse() const
	{
		Matrix4f Ret;

		float Det = Determinant();

		if (Det < EPSILON_FLOAT && Det > -1.0f * EPSILON_FLOAT)
		{
			DEBUG_ERROR("Singular Matrix Cannot Invert");
		}

		float InverseDeterminant = 1.0f / Det;

		Ret.m_Data[0][0] =		   InverseDeterminant * Determinant(m_Data[1][1], m_Data[1][2], m_Data[1][3], m_Data[2][1], m_Data[2][2], m_Data[2][3], m_Data[3][1], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[1][0] = -1.0f * InverseDeterminant * Determinant(m_Data[1][0], m_Data[1][2], m_Data[1][3], m_Data[2][0], m_Data[2][2], m_Data[2][3], m_Data[3][0], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[2][0] =         InverseDeterminant * Determinant(m_Data[1][0], m_Data[1][1], m_Data[1][3], m_Data[2][0], m_Data[2][1], m_Data[2][3], m_Data[3][0], m_Data[3][1], m_Data[3][3]);
		Ret.m_Data[3][0] = -1.0f * InverseDeterminant * Determinant(m_Data[1][0], m_Data[1][1], m_Data[1][2], m_Data[2][0], m_Data[2][1], m_Data[2][2], m_Data[3][0], m_Data[3][1], m_Data[3][2]);

		Ret.m_Data[0][1] = -1.0f * InverseDeterminant * Determinant(m_Data[0][1], m_Data[0][2], m_Data[0][3], m_Data[2][1], m_Data[2][2], m_Data[2][3], m_Data[3][1], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[1][1] =         InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][2], m_Data[0][3], m_Data[2][0], m_Data[2][2], m_Data[2][3], m_Data[3][0], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[2][1] = -1.0f * InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][3], m_Data[2][0], m_Data[2][1], m_Data[2][3], m_Data[3][0], m_Data[3][1], m_Data[3][3]);
		Ret.m_Data[3][1] =         InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][2], m_Data[2][0], m_Data[2][1], m_Data[2][2], m_Data[3][0], m_Data[3][1], m_Data[3][2]);

		Ret.m_Data[0][2] =         InverseDeterminant * Determinant(m_Data[0][1], m_Data[0][2], m_Data[0][3], m_Data[1][1], m_Data[1][2], m_Data[1][3], m_Data[3][1], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[1][2] = -1.0f * InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][2], m_Data[0][3], m_Data[1][0], m_Data[1][2], m_Data[1][3], m_Data[3][0], m_Data[3][2], m_Data[3][3]);
		Ret.m_Data[2][2] =         InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][3], m_Data[1][0], m_Data[1][1], m_Data[1][3], m_Data[3][0], m_Data[3][1], m_Data[3][3]);
		Ret.m_Data[3][2] = -1.0f * InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][2], m_Data[1][0], m_Data[1][1], m_Data[1][2], m_Data[3][0], m_Data[3][1], m_Data[3][2]);

		Ret.m_Data[0][3] = -1.0f * InverseDeterminant * Determinant(m_Data[0][1], m_Data[0][2], m_Data[0][3], m_Data[1][1], m_Data[1][2], m_Data[1][3], m_Data[2][1], m_Data[2][2], m_Data[2][3]);
		Ret.m_Data[1][3] =         InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][2], m_Data[0][3], m_Data[1][0], m_Data[1][2], m_Data[1][3], m_Data[2][0], m_Data[2][2], m_Data[2][3]);
		Ret.m_Data[2][3] = -1.0f * InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][3], m_Data[1][0], m_Data[1][1], m_Data[1][3], m_Data[2][0], m_Data[2][1], m_Data[2][3]);
		Ret.m_Data[3][3] =         InverseDeterminant * Determinant(m_Data[0][0], m_Data[0][1], m_Data[0][2], m_Data[1][0], m_Data[1][1], m_Data[1][2], m_Data[2][0], m_Data[2][1], m_Data[2][2]);

		return Ret;
	}

	Matrix4f Matrix4f::Transpose() const
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			for (auto Column = 0; Column < 4; Column++)
			{
				Ret.m_Data[Row][Column] = m_Data[Column][Row];
			}
		}
		return Ret;
	}

	float Matrix4f::Determinant() const
	{
		return
			m_Data[0][0] * Determinant(m_Data[1][1], m_Data[1][2], m_Data[1][3], m_Data[2][1], m_Data[2][2], m_Data[2][3], m_Data[3][1], m_Data[3][2], m_Data[3][3]) -
			m_Data[0][1] * Determinant(m_Data[1][0], m_Data[1][2], m_Data[1][3], m_Data[2][0], m_Data[2][2], m_Data[2][3], m_Data[3][0], m_Data[3][2], m_Data[3][3]) +
			m_Data[0][2] * Determinant(m_Data[1][0], m_Data[1][1], m_Data[1][3], m_Data[2][0], m_Data[2][1], m_Data[2][3], m_Data[3][0], m_Data[3][1], m_Data[3][3]) -
			m_Data[0][3] * Determinant(m_Data[1][0], m_Data[1][1], m_Data[1][2], m_Data[2][0], m_Data[2][1], m_Data[2][2], m_Data[3][0], m_Data[3][1], m_Data[3][2]);
	}

	float Matrix4f::Determinant(
		float A11, float A12, float A13, 
		float A21, float A22, float A23, 
		float A31, float A32, float A33) const
	{
		return 
			A11 * Determinant(A22, A23, A32, A33) - 
			A12 * Determinant(A21, A23, A31, A33) + 
			A13 * Determinant(A21, A22, A31, A32);
	}

	float Matrix4f::Determinant(
		float A11, float A12, 
		float A21, float A22) const
	{
		return A11 * A22 - A12 * A21;
	}
}