#pragma once

#ifndef __VECTOR_2F__
#define __VECTOR_2F__

#include "Math\Dependency\MathDependency.h"
#include "Math\Dependency\MathMacro.h"

namespace EasyMath
{

	class Vector2f
	{

	private:

		float m_X, m_Y;

	public:

		Vector2f();
		Vector2f(float X, float Y);
		Vector2f(const Vector2f& Other);

	public:

		friend Vector2f operator + (const Vector2f& Vector1, const Vector2f& Vector2);
		friend Vector2f operator - (const Vector2f& Vector1, const Vector2f& Vector2);
		friend Vector2f operator * (const Vector2f& Vector, float Scale);
		friend Vector2f operator * (float Scale, const Vector2f& Vector);
		friend Vector2f operator / (const Vector2f& Vector, float Scale);

	public:

		friend std::ostream& operator << (std::ostream &Out, const Vector2f &Vector);
		friend std::istream& operator >> (std::istream &In, Vector2f &Vector);

	public:

		bool operator == (const Vector2f& Vector) const;
		bool operator != (const Vector2f& Vector) const;
		Vector2f& operator = (const Vector2f& Vector);
		Vector2f& operator += (const Vector2f& Vector);
		Vector2f& operator -= (const Vector2f& Vector);
		Vector2f& operator *= (float Scale);
		Vector2f& operator /= (float Scale);
		Vector2f operator - () const;

	public:

		float& X();
		float& Y();
		float X() const;
		float Y() const;
		float Length() const;
		float SqrLength() const;
		Vector2f Zero() const;
		void Normalize();
		Vector2f Normal() const;
		void Negate();
		Vector2f Negation() const;
		float Dot(const Vector2f& Vector) const;

	};
}

#endif