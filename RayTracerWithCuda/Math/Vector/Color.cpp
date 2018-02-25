#include "stdafx.h"

#include "Color.h"

namespace EasyMath
{

	Color::Color() : m_R(0.0f), m_G(0.0f), m_B(0.0f)
	{

	}

	Color::Color(float R, float G, float B) : m_R(R), m_G(G), m_B(B)
	{
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
	}

	Color operator + (const Color& Colour, float Value)
	{
		return Color(Colour.m_R + Value, Colour.m_G + Value, Colour.m_B + Value);
	}

	Color operator - (const Color& Colour, float Value)
	{
		return Color(Colour.m_R - Value, Colour.m_G - Value, Colour.m_B - Value);
	}

	Color operator / (const Color& Colour, float Value)
	{
		return Color(Colour.m_R / Value, Colour.m_G / Value, Colour.m_B / Value);
	}

	Color operator * (const Color& Colour, float Value)
	{
		return Color(Colour.m_R * Value, Colour.m_G * Value, Colour.m_B * Value);
	}

	Color operator * (float Value, const Color& Colour)
	{
		return Color(Colour.m_R * Value, Colour.m_G * Value, Colour.m_B * Value);
	}

	std::ostream& operator << (std::ostream& Out, const Color& Colour)
	{
		Out << "Color <" << Colour.m_R << ", " << Colour.m_G << ", " << Colour.m_B << ")";
		return Out;
	}

	std::istream& operator >> (std::istream& In, Color& Colour)
	{
		In >> Colour.m_R >> Colour.m_G >> Colour.m_B;
		ClampRef(Colour.m_R, 0.0f, 1.0f);
		ClampRef(Colour.m_G, 0.0f, 1.0f);
		ClampRef(Colour.m_B, 0.0f, 1.0f);
		return In;
	}

	bool Color::operator == (const Color& Colour) const
	{
		return m_R == Colour.m_R && m_G == Colour.m_G && m_B == Colour.m_B;
	}

	bool Color::operator != (const Color& Colour) const
	{
		return m_R != Colour.m_R || m_G != Colour.m_G || m_B != Colour.m_B;
	}

	Color Color::operator * (const Color& Colour) const
	{
		return Color(m_R * Colour.m_R, m_G * Colour.m_G, m_B * Colour.m_B);
	}

	Color Color::operator + (const Color& Colour) const
	{
		return Color(m_R + Colour.m_R, m_G + Colour.m_G, m_B + Colour.m_B);
	}

	Color& Color::operator = (const Color& Colour)
	{
		if (this != &Colour)
		{
			m_R = Colour.m_R;
			m_G = Colour.m_G;
			m_B = Colour.m_B;
		}
		return *this;
	}

	Color& Color::operator +=(const Color& Colour)
	{
		m_R += Colour.m_R;
		m_G += Colour.m_G;
		m_B += Colour.m_B;
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	Color& Color::operator += (float Value)
	{
		m_R += Value;
		m_G += Value;
		m_B += Value;
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	Color& Color::operator -= (float Value)
	{
		m_R -= Value;
		m_G -= Value;
		m_B -= Value;
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	Color& Color::operator *= (float Value)
	{
		m_R *= Value;
		m_G *= Value;
		m_B *= Value;
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	Color& Color::operator *= (Vector3f& Vector)
	{
		m_R *= Vector.X();
		m_G *= Vector.Y();
		m_B *= Vector.Z();
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	Color& Color::operator /= (float Value)
	{
		m_R /= Value;
		m_G /= Value;
		m_B /= Value;
		ClampRef(m_R, 0.0f, 1.0f);
		ClampRef(m_G, 0.0f, 1.0f);
		ClampRef(m_B, 0.0f, 1.0f);
		return *this;
	}

	float& Color::R()
	{
		return m_R;
	}

	float& Color::G()
	{
		return m_G;
	}

	float& Color::B()
	{
		return m_B;
	}

	float Color::R() const
	{
		return m_R;
	}

	float Color::G() const
	{
		return m_G;
	}

	float Color::B() const
	{
		return m_B;
	}
}


