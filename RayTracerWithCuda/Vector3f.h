#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

namespace EasyMath
{

	class Vector3f
	{
		
	private:

		float m_X, m_Y, m_Z;

	public:

		Vector3f();
		Vector3f(float X, float Y, float Z);
		Vector3f(const Vector3f& Other);

	public:

		friend Vector3f operator + (const Vector3f& Vector1, const Vector3f& Vector2);
		friend Vector3f operator - (const Vector3f& Vector1, const Vector3f& Vector2);
		friend Vector3f operator * (const Vector3f& Vector, float Scale);
		friend Vector3f operator * (float Scale, const Vector3f& Vector);
		friend Vector3f operator / (const Vector3f& Vector, float Scale);

	public:

		friend std::ostream& operator << (std::ostream &Out, const Vector3f &Vector);
		friend std::istream& operator >> (std::istream &In, Vector3f &Vector);

	public:

		bool operator == (const Vector3f& Vector) const;
		bool operator != (const Vector3f& Vector) const;
		Vector3f& operator = (const Vector3f& Vector);
		Vector3f& operator += (const Vector3f& Vector);
		Vector3f& operator -= (const Vector3f& Vector);
		Vector3f& operator *= (float Scale);
		Vector3f& operator /= (float Scale);
		Vector3f operator - () const;

	public:

		float& X();
		float& Y();
		float& Z();
		float X() const;
		float Y() const;
		float Z() const;
		float Length() const;
		float SqrLength() const;
		Vector3f Zero() const;
		void Normalize();
		Vector3f Normal() const;
		void Negate();
		Vector3f Negation() const;
		Vector3f Cross(const Vector3f& Vector) const;
		float Dot(const Vector3f& Vector) const;

	};
}