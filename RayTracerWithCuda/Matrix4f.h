#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

namespace EasyMath
{

	class Matrix4f
	{

		friend class Matrix4f;

	private:

		float m_Data[4][4];

	public:

		Matrix4f();
		Matrix4f(
			float A11, float A12, float A13, float A14,
			float A21, float A22, float A23, float A24,
			float A31, float A32, float A33, float A34,
			float A41, float A42, float A43, float A44
		);
		Matrix4f(const Matrix4f& other);

	public:

		friend Matrix4f operator + (const Matrix4f& Matrix, float Scale);
		friend Matrix4f operator - (const Matrix4f& Matrix, float Scale);
		friend Matrix4f operator * (const Matrix4f& Matrix, float Scale);
		friend Matrix4f operator * (float Scale, const Matrix4f& Matrix);
		friend Matrix4f operator / (const Matrix4f& Matrix, float Scale);

	public:

		float& operator () (Int32 Row, Int32 Column);
		bool operator == (const Matrix4f& Other) const;
		Matrix4f& operator = (const Matrix4f& Other);
		Matrix4f& operator += (const Matrix4f& Matrix);
		Matrix4f& operator -= (const Matrix4f& Matrix);
		Matrix4f& operator *= (const Matrix4f& Matrix);
		Matrix4f& operator *= (float Scale);
		Matrix4f operator - () const;

	};
}