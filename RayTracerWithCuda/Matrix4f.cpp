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

	float& Matrix4f::operator () (Int32 Row, Int32 Column)
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
}