#include "stdafx.h"

#include "Color.h"

namespace EasyTools
{
	Color::Color() : m_R(0), m_G(0), m_B(0)
	{

	}

	Color::Color(uint8 R, uint8 G, uint8 B) : m_R(R), m_G(G), m_B(B)
	{

	}

	Color operator + (const Color& Colour, uint8 Value)
	{
		return Color(Colour.m_R + Value, Colour.m_G + Value, Colour.m_B + Value);
	}

	Color operator - (const Color& Colour, uint8 Value)
	{
		return Color(Colour.m_R - Value, Colour.m_G - Value, Colour.m_B - Value);
	}

	Color operator / (const Color& Colour, uint8 Value)
	{
		return Color(Colour.m_R / Value, Colour.m_G / Value, Colour.m_B / Value);
	}

	Color operator * (const Color& Colour, uint8 Value)
	{
		return Color(Colour.m_R * Value, Colour.m_G * Value, Colour.m_B * Value);
	}

	Color operator * (uint8 Value, const Color& Colour)
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

	Color& Color::operator += (uint8 Value)
	{
		m_R += Value;
		m_G += Value;
		m_B += Value;
		return *this;
	}

	Color& Color::operator -= (uint8 Value)
	{
		m_R -= Value;
		m_G -= Value;
		m_B -= Value;
		return *this;
	}

	Color& Color::operator *= (uint8 Value)
	{
		m_R *= Value;
		m_G *= Value;
		m_B *= Value;
		return *this;
	}

	Color& Color::operator /= (uint8 Value)
	{
		m_R /= Value;
		m_G /= Value;
		m_B /= Value;
		return *this;
	}

	uint8& Color::R()
	{
		return m_R;
	}

	uint8& Color::G()
	{
		return m_G;
	}

	uint8& Color::B()
	{
		return m_B;
	}

	uint8 Color::R() const
	{
		return m_R;
	}

	uint8 Color::G() const
	{
		return m_G;
	}

	uint8 Color::B() const
	{
		return m_B;
	}

}


