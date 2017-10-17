#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

namespace EasyMath
{

	class Color
	{

	private:

		uint8 m_R, m_G, m_B;

	public:

		Color();
		Color(uint8 R, uint8 G, uint8 B);

	public:

		friend Color operator + (const Color& Colour, uint8 Value);
		friend Color operator - (const Color& Colour, uint8 Value);
		friend Color operator / (const Color& Colour, uint8 Value);
		friend Color operator * (const Color& Colour, uint8 Value);
		friend Color operator * (uint8 Value, const Color& Colour);
	
	public:

		friend std::ostream& operator << (std::ostream &Out, const Color &Color);
		friend std::istream& operator >> (std::istream &In, Color &Color);

	public:

		bool operator == (const Color& Colour) const;
		bool operator != (const Color& Colour) const;
		Color& operator = (const Color& Colour);
		Color& operator += (uint8 Value);
		Color& operator -= (uint8 Value);
		Color& operator *= (uint8 Value);
		Color& operator /= (uint8 Value);

	public:

		uint8& R();
		uint8& G();
		uint8& B();
		uint8 R() const;
		uint8 G() const;
		uint8 B() const;

	};
}