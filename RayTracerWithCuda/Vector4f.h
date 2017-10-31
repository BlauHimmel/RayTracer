#pragma once

#ifndef __VECTOR_4F__
#define __VECTOR_4F__

#include "MathDependency.h"
#include "MathMacro.h"

namespace EasyMath
{

	class Vector4f
	{

	public:

		friend class Transform;

	private:

		float m_X, m_Y, m_Z, m_W;
		
	public:

		Vector4f();
		Vector4f(float X, float Y, float Z, float W);
		Vector4f(const Vector4f& Other);

	public:

		friend Vector4f operator + (const Vector4f& Vector1, const Vector4f& Vector2);
		friend Vector4f operator - (const Vector4f& Vector1, const Vector4f& Vector2);
		friend Vector4f operator * (const Vector4f& Vector, float Scale);
		friend Vector4f operator * (float Scale, const Vector4f& Vector);
		friend Vector4f operator / (const Vector4f& Vector, float Scale);

	public:

		friend std::ostream& operator << (std::ostream &Out, const Vector4f &Vector);
		friend std::istream& operator >> (std::istream &In, Vector4f &Vector);

	public:

		bool operator == (const Vector4f& Vector) const;
		bool operator != (const Vector4f& Vector) const;
		Vector4f& operator = (const Vector4f& Vector);
		Vector4f& operator += (const Vector4f& Vector);
		Vector4f& operator -= (const Vector4f& Vector);
		Vector4f& operator *= (float Scale);
		Vector4f& operator /= (float Scale);
		Vector4f operator - () const;

	public:

		float& X();
		float& Y();
		float& Z();
		float& W();
		float X() const;
		float Y() const;
		float Z() const;
		float W() const;
		float Length() const;
		float SqrLength() const;
		Vector4f Zero() const;
		void Normalize();
		Vector4f Normal() const;
		void Negate();
		Vector4f Negation() const;
		float Dot(const Vector4f& Vector) const;

	};
}

#endif