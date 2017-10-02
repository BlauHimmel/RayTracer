#include "stdafx.h"

#include "Vector2f.h"

namespace EasyMath
{
	Vector2f::Vector2f() : m_X(0.0f), m_Y(0.0f)
	{

	}

	Vector2f::Vector2f(float X, float Y) : m_X(X), m_Y(Y)
	{

	}

	Vector2f::Vector2f(const Vector2f& Other)
	{
		m_X = Other.m_X;
		m_Y = Other.m_Y;
	}

	Vector2f operator + (const Vector2f& Vector1, const Vector2f& Vector2)
	{
		Vector2f Ret;
		Ret.m_X = Vector1.m_X + Vector2.m_X;
		Ret.m_Y = Vector1.m_Y + Vector2.m_Y;
		return Ret;
	}

	Vector2f operator - (const Vector2f& Vector1, const Vector2f& Vector2)
	{
		Vector2f Ret;
		Ret.m_X = Vector1.m_X - Vector2.m_X;
		Ret.m_Y = Vector1.m_Y - Vector2.m_Y;
		return Ret;
	}

	Vector2f operator * (const Vector2f& Vector, float Scale)
	{
		Vector2f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		return Ret;
	}

	Vector2f operator * (float Scale, const Vector2f& Vector)
	{
		Vector2f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		return Ret;
	}

	Vector2f operator / (const Vector2f& Vector, float Scale)
	{
		Vector2f Ret;
		Ret.m_X = Vector.m_X / Scale;
		Ret.m_Y = Vector.m_Y / Scale;
		return Ret;
	}

	std::ostream& operator << (std::ostream& Out, const Vector2f& Vector)
	{
		Out << "Vector2f <" << Vector.m_X << ", " << Vector.m_Y << ">";
		return Out;
	}

	std::istream& operator >> (std::istream& In, Vector2f& Vector)
	{
		In >> Vector.m_X >> Vector.m_Y;
		return In;
	}

	bool Vector2f::operator == (const Vector2f& Vector) const
	{
		return m_X == Vector.m_X && m_Y == Vector.m_Y;
	}

	Vector2f& Vector2f::operator = (const Vector2f& Vector)
	{
		if (this != &Vector)
		{
			m_X = Vector.m_X;
			m_Y = Vector.m_Y;
		}
		return *this;
	}

	Vector2f& Vector2f::operator += (const Vector2f& Vector)
	{
		this->m_X += Vector.m_X;
		this->m_Y += Vector.m_Y;
		return *this;
	}

	Vector2f& Vector2f::operator -= (const Vector2f& Vector)
	{
		this->m_X -= Vector.m_X;
		this->m_Y -= Vector.m_Y;
		return *this;
	}

	Vector2f& Vector2f::operator *= (float Scale)
	{
		this->m_X *= Scale;
		this->m_Y *= Scale;
		return *this;
	}

	Vector2f& Vector2f::operator /= (float Scale)
	{
		this->m_X /= Scale;
		this->m_Y /= Scale;
		return *this;
	}

	Vector2f Vector2f::operator - () const
	{
		Vector2f Ret;
		Ret.m_X = -1.0f * m_X;
		Ret.m_Y = -1.0f * m_Y;
		return Ret;
	}

	float& Vector2f::X()
	{
		return m_X;
	}

	float& Vector2f::Y()
	{
		return m_Y;
	}

	float Vector2f::X() const
	{
		return m_X;
	}

	float Vector2f::Y() const
	{
		return m_Y;
	}

	float Vector2f::Length() const
	{
		return sqrtf(m_X * m_X + m_Y * m_Y);
	}

	float Vector2f::SqrLength() const
	{
		return m_X * m_X + m_Y * m_Y;
	}

	Vector2f Vector2f::Zero() const
	{
		return Vector2f(0.0f, 0.0f);
	}

	void Vector2f::Normalize()
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y);
		m_X *= InverseSqrtLength;
		m_Y *= InverseSqrtLength;
	}

	Vector2f Vector2f::Normal() const
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y);
		Vector2f Ret;
		Ret.m_X = m_X * InverseSqrtLength;
		Ret.m_Y = m_Y * InverseSqrtLength;
		return Ret;
	}

	void Vector2f::Negate()
	{
		m_X *= -1.0f;
		m_Y *= -1.0f;
	}

	Vector2f Vector2f::Negation() const
	{
		Vector2f Ret;
		Ret.m_X *= -1.0f;
		Ret.m_Y *= -1.0f;
		return Vector2f();
	}

	float Vector2f::Dot(const Vector2f& Vector) const
	{
		return m_X * Vector.m_X + m_Y * Vector.m_Y;
	}
}
