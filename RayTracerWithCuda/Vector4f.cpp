#include "stdafx.h"

#include "Vector4f.h"

namespace EasyMath
{

	Vector4f::Vector4f() : m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_W(0.0f)
	{

	}

	Vector4f::Vector4f(float X, float Y, float Z, float W) : m_X(X), m_Y(Y), m_Z(Z), m_W(W)
	{

	}

	Vector4f::Vector4f(const Vector4f& Other)
	{
		m_X = Other.m_X;
		m_Y = Other.m_Y;
		m_Z = Other.m_Z;
		m_W = Other.m_W;
	}

	Vector4f operator + (const Vector4f& Vector1, const Vector4f& Vector2)
	{
		Vector4f Ret;
		Ret.m_X = Vector1.m_X + Vector2.m_X;
		Ret.m_Y = Vector1.m_Y + Vector2.m_Y;
		Ret.m_Z = Vector1.m_Z + Vector2.m_Z;
		Ret.m_W = Vector1.m_W + Vector2.m_W;
		return Ret;
	}

	Vector4f operator - (const Vector4f& Vector1, const Vector4f& Vector2)
	{
		Vector4f Ret;
		Ret.m_X = Vector1.m_X - Vector2.m_X;
		Ret.m_Y = Vector1.m_Y - Vector2.m_Y;
		Ret.m_Z = Vector1.m_Z - Vector2.m_Z;
		Ret.m_W = Vector1.m_W - Vector2.m_W;
		return Ret;
	}

	Vector4f operator * (const Vector4f& Vector, float Scale)
	{
		Vector4f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		Ret.m_Z = Vector.m_Z * Scale;
		Ret.m_W = Vector.m_W * Scale;
		return Ret;
	}

	Vector4f operator * (float Scale, const Vector4f& Vector)
	{
		Vector4f Ret;
		Ret.m_X = Vector.m_X * Scale;
		Ret.m_Y = Vector.m_Y * Scale;
		Ret.m_Z = Vector.m_Z * Scale;
		Ret.m_W = Vector.m_W * Scale;
		return Ret;
	}

	Vector4f operator / (const Vector4f& Vector, float Scale)
	{
		Vector4f Ret;
		Ret.m_X = Vector.m_X / Scale;
		Ret.m_Y = Vector.m_Y / Scale;
		Ret.m_Z = Vector.m_Z / Scale;
		Ret.m_W = Vector.m_W / Scale;
		return Ret;
	}

	std::ostream& operator << (std::ostream& Out, const Vector4f& Vector)
	{
		Out << "Vector4f <" << Vector.m_X << ", " << Vector.m_Y << ", " << Vector.m_Z << ", " << Vector.m_W << ">";
		return Out;
	}

	std::istream& operator >> (std::istream& In, Vector4f& Vector)
	{
		In >> Vector.m_X >> Vector.m_Y >> Vector.m_Z >> Vector.m_W;
		return In;
	}

	bool Vector4f::operator == (const Vector4f& Vector) const
	{
		return m_X == Vector.m_X && m_Y == Vector.m_Y && m_Z == Vector.m_Z && m_W == Vector.m_W;
	}

	bool Vector4f::operator != (const Vector4f& Vector) const
	{
		return m_X != Vector.m_X || m_Y != Vector.m_Y || m_Z != Vector.m_Z || m_W != Vector.m_W;
	}

	Vector4f& Vector4f::operator = (const Vector4f& Vector)
	{
		if (this != &Vector)
		{
			m_X = Vector.m_X;
			m_Y = Vector.m_Y;
			m_Z = Vector.m_Z;
			m_W = Vector.m_W;
		}
		return *this;
	}

	Vector4f& Vector4f::operator += (const Vector4f& Vector)
	{
		this->m_X += Vector.m_X;
		this->m_Y += Vector.m_Y;
		this->m_Z += Vector.m_Z;
		this->m_W += Vector.m_W;
		return *this;
	}

	Vector4f& Vector4f::operator -= (const Vector4f& Vector)
	{
		this->m_X -= Vector.m_X;
		this->m_Y -= Vector.m_Y;
		this->m_Z -= Vector.m_Z;
		this->m_W -= Vector.m_W;
		return *this;
	}

	Vector4f& Vector4f::operator *= (float Scale)
	{
		this->m_X *= Scale;
		this->m_Y *= Scale;
		this->m_Z *= Scale;
		this->m_W *= Scale;
		return *this;
	}

	Vector4f& Vector4f::operator /= (float Scale)
	{
		this->m_X /= Scale;
		this->m_Y /= Scale;
		this->m_Z /= Scale;
		this->m_W /= Scale;
		return *this;
	}

	Vector4f Vector4f::operator - () const
	{
		Vector4f Ret;
		Ret.m_X = -1.0f * m_X;
		Ret.m_Y = -1.0f * m_Y;
		Ret.m_Z = -1.0f * m_Z;
		Ret.m_W = -1.0f * m_W;
		return Ret;
	}

	float& Vector4f::X()
	{
		return m_X;
	}

	float& Vector4f::Y()
	{
		return m_Y;
	}

	float& Vector4f::Z()
	{
		return m_Z;
	}

	float& Vector4f::W()
	{
		return m_W;
	}

	float Vector4f::X() const
	{
		return m_X;
	}

	float Vector4f::Y() const
	{
		return m_Y;
	}

	float Vector4f::Z() const
	{
		return m_Z;
	}

	float Vector4f::W() const
	{
		return m_W;
	}

	float Vector4f::Length() const
	{
		return sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);
	}

	float Vector4f::SqrLength() const
	{
		return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
	}

	Vector4f Vector4f::Zero() const
	{
		return Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void Vector4f::Normalize()
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);
		m_X *= InverseSqrtLength;
		m_Y *= InverseSqrtLength;
		m_Z *= InverseSqrtLength;
		m_W *= InverseSqrtLength;
	}

	Vector4f Vector4f::Normal() const
	{
		float InverseSqrtLength = 1.0f / sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);
		Vector4f Ret;
		Ret.m_X = m_X * InverseSqrtLength;
		Ret.m_Y = m_Y * InverseSqrtLength;
		Ret.m_Z = m_Z * InverseSqrtLength;
		Ret.m_W = m_W * InverseSqrtLength;
		return Ret;
	}

	void Vector4f::Negate()
	{
		m_X *= -1.0f;
		m_Y *= -1.0f;
		m_Z *= -1.0f;
		m_W *= -1.0f;
	}

	Vector4f Vector4f::Negation() const
	{
		Vector4f Ret;
		Ret.m_X *= -1.0f;
		Ret.m_Y *= -1.0f;
		Ret.m_Z *= -1.0f;
		Ret.m_W *= -1.0f;
		return Ret;
	}

	float Vector4f::Dot(const Vector4f& Vector) const
	{
		return m_X * Vector.m_X + m_Y * Vector.m_Y + m_Z * Vector.m_Z + m_W * Vector.m_W;
	}
}
