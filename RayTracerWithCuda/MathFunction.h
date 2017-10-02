#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace EasyMath
{
	
	inline bool NearlyEqual(float A, float B, float Epsilon = EPSILON_FLOAT)
	{
		return A - B < Epsilon && A - B > -Epsilon;
	}
	
	inline bool NearlyEqual(double A, double B, double Epsilon = EPSILON_DOUBLE)
	{
		return A - B < Epsilon && A - B > -Epsilon;
	}

	inline bool NearlyZero(float A, float Epsilon = EPSILON_FLOAT)
	{
		return A < Epsilon && A > -Epsilon;
	}

	inline bool NearlyZero(double A, double Epsilon = EPSILON_DOUBLE)
	{
		return A < Epsilon && A > -Epsilon;
	}

	inline float Interpolate(float A, float B, float T)
	{
		return A + (B - A) * T;
	}

	inline double Interpolate(double A, double B, double T)
	{
		return A + (B - A) * T;
	}

	inline Vector2f Interpolate(const Vector2f& VectorA, const Vector2f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	inline Vector3f Interpolate(const Vector3f& VectorA, const Vector3f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	inline Vector4f Interpolate(const Vector4f& VectorA, const Vector4f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	inline float Range(float Value, float Min, float Max)
	{
		if (Value < Min)
		{
			return Min;
		}
		if (Value > Max)
		{
			return Max;
		}
		return Value;
	}

	inline double Range(double Value, double Min, double Max)
	{
		if (Value < Min)
		{
			return Min;
		}
		if (Value > Max)
		{
			return Max;
		}
		return Value;
	}

	template<typename TValue>
	inline TValue Abs(TValue Value)
	{
		return Value < 0 ? -Value : Value;
	}

	template<typename TValue>
	inline void Swap(TValue& A, TValue& B)
	{
		TValue Temp(A);
		A = std::move(B);
		B = std::move(Temp);
	}
}