#include "stdafx.h"

#include "Vector3f.h"

namespace EasyMath
{
	Vector3f::Vector3f() : m_X(0.0f), m_Y(0.0f), m_Z(0.0f)
	{

	}

	Vector3f::Vector3f(float X, float Y, float Z) : m_X(X), m_Y(Y), m_Z(Z)
	{

	}

	Vector3f::Vector3f(const Vector3f& Other)
	{
		m_X = Other.m_X;
		m_Y = Other.m_Y;
		m_Z = Other.m_Z;
	}

	Vector3f operator + (const Vector3f& Vector1, const Vector3f& Vector2)
	{
		Vector3f Ret;
		Ret.m_X = Vector1.m_X + Vector2.m_X;
		Ret.m_Y = Vector1.m_Y + Vector2.m_Y;
		Ret.m_Z = Vector1.m_Z + Vector2.m_Z;
		return Ret;
	}

	Vector3f operator - (const Vector3f& Vector1, const Vector3f& Vector2)
	{
		Vector3f Ret;
		Ret.m_X = Vector1.m_X - Vector2.m_X;
		Ret.m_Y = Vector1.m_Y - Vector2.m_Y;
		Ret.m_Z = Vector1.m_Z - Vector2.m_Z;
		return Ret;
	}

	Vector3f operator * (const Vector3f& Vector, float Scale)
	{
		Vector3f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		Ret.m_Z = Vector.m_Z * Scale;
		return Ret;
	}

	Vector3f operator * (float Scale, const Vector3f& Vector)
	{
		Vector3f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		Ret.m_Z = Vector.m_Z * Scale;
		return Ret;
	}

	Vector3f operator / (const Vector3f& Vector, float Scale)
	{
		Vector3f Ret;
		Ret.m_X = Vector.m_X / Scale;
		Ret.m_Y = Vector.m_Y / Scale;
		Ret.m_Z = Vector.m_Z / Scale;
		return Ret;
	}

	std::ostream& operator << (std::ostream& Out, const Vector3f& Vector)
	{
		Out << "Vector3f <" << Vector.m_X << ", " << Vector.m_Y << ", " << Vector.m_Z << ">";
		return Out;
	}

	std::istream& operator >> (std::istream& In, Vector3f& Vector)
	{
		In >> Vector.m_X >> Vector.m_Y >> Vector.m_Z;
		return In;
	}

	bool Vector3f::operator == (const Vector3f& Vector) const
	{
		return m_X == Vector.m_X && m_Y == Vector.m_Y && m_Z == Vector.m_Z;
	}

	Vector3f& Vector3f::operator = (const Vector3f& Vector)
	{
		if (this != &Vector)
		{
			m_X = Vector.m_X;
			m_Y = Vector.m_Y;
			m_Z = Vector.m_Z;
		}
		return *this;
	}

	Vector3f& Vector3f::operator += (const Vector3f& Vector)
	{
		this->m_X += Vector.m_X;
		this->m_Y += Vector.m_Y;
		this->m_Z += Vector.m_Z;
		return *this;
	}

	Vector3f& Vector3f::operator -= (const Vector3f& Vector)
	{
		this->m_X -= Vector.m_X;
		this->m_Y -= Vector.m_Y;
		this->m_Z -= Vector.m_Z;
		return *this;
	}

	Vector3f& Vector3f::operator *= (float Scale)
	{
		this->m_X *= Scale;
		this->m_Y *= Scale;
		this->m_Z *= Scale;
		return *this;
	}

	Vector3f& Vector3f::operator /= (float Scale)
	{
		this->m_X /= Scale;
		this->m_Y /= Scale;
		this->m_Z /= Scale;
		return *this;
	}

	Vector3f Vector3f::operator - () const
	{
		Vector3f Ret;
		Ret.m_X = -1.0f * m_X;
		Ret.m_Y = -1.0f * m_Y;
		Ret.m_Z = -1.0f * m_Z;
		return Ret;
	}

	float& Vector3f::X()
	{
		return m_X;
	}

	float& Vector3f::Y()
	{
		return m_Y;
	}

	float& Vector3f::Z()
	{
		return m_Z;
	}

	float Vector3f::X() const
	{
		return m_X;
	}

	float Vector3f::Y() const
	{
		return m_Y;
	}

	float Vector3f::Z() const
	{
		return m_Z;
	}

	float Vector3f::Length() const
	{
		return sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}

	float Vector3f::SqrLength() const
	{
		return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
	}

	Vector3f Vector3f::Zero() const
	{
		return Vector3f(0.0f, 0.0f, 0.0f);
	}

	void Vector3f::Normalize()
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
		m_X *= InverseSqrtLength;
		m_Y *= InverseSqrtLength;
		m_Z *= InverseSqrtLength;
	}

	Vector3f Vector3f::Normal() const
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
		Vector3f Ret;
		Ret.m_X = m_X * InverseSqrtLength;
		Ret.m_Y = m_Y * InverseSqrtLength;
		Ret.m_Z = m_Z * InverseSqrtLength;
		return Ret;
	}

	void Vector3f::Negate()
	{
		m_X *= -1.0f;
		m_Y *= -1.0f;
		m_Z *= -1.0f;
	}

	Vector3f Vector3f::Negation() const
	{
		Vector3f Ret;
		Ret.m_X *= -1.0f;
		Ret.m_Y *= -1.0f;
		Ret.m_Z *= -1.0f;
		return Ret;
	}

	Vector3f Vector3f::Cross(const Vector3f& Vector) const
	{
		Vector3f Ret;
		Ret.m_X = m_Y * Vector.m_Z - m_Z * Vector.m_Y;
		Ret.m_Y = m_Z * Vector.m_X - m_X * Vector.m_Z;
		Ret.m_Z = m_X * Vector.m_Y - m_Y * Vector.m_X;
		return Ret;
	}

	float Vector3f::Dot(const Vector3f& Vector) const
	{
		return m_X * Vector.m_X + m_Y * Vector.m_Y + m_Z * Vector.m_Z;
	}
}
