#pragma once

#ifndef __COLOR__
#define __COLOR__

#include "Math\Dependency\MathDependency.h"
#include "Math\Dependency\MathMacro.h"

#include "Math\Common\MathFunction.hpp"
#include "Math\Vector\Vector3f.h"

namespace EasyMath
{

	class Color
	{

	private:

		float m_R, m_G, m_B;

	public:

		Color();
		Color(float R, float G, float B);

	public:

		friend Color operator + (const Color& Colour, float Value);
		friend Color operator - (const Color& Colour, float Value);
		friend Color operator / (const Color& Colour, float Value);
		friend Color operator * (const Color& Colour, float Value);
		friend Color operator * (float Value, const Color& Colour);
	
	public:

		friend std::ostream& operator << (std::ostream &Out, const Color &Color);
		friend std::istream& operator >> (std::istream &In, Color &Color);

	public:

		bool operator == (const Color& Colour) const;
		bool operator != (const Color& Colour) const;
		Color operator * (const Color& Colour) const;
		Color operator + (const Color& Colour) const;
		Color& operator = (const Color& Colour);
		Color& operator += (const Color& Colour);
		Color& operator += (float Value);
		Color& operator -= (float Value);
		Color& operator *= (float Value);
		Color& operator *= (Vector3f& Vector);
		Color& operator /= (float Value);

	public:

		float& R();
		float& G();
		float& B();
		float R() const;
		float G() const;
		float B() const;

	};
}

#endif