#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace EasyMath
{
	
	FORCE_INLINE bool NearlyEqual(float A, float B, float Epsilon = EPSILON_FLOAT)
	{
		return A - B < Epsilon && A - B > -Epsilon;
	}
	
	FORCE_INLINE bool NearlyEqual(double A, double B, double Epsilon = EPSILON_DOUBLE)
	{
		return A - B < Epsilon && A - B > -Epsilon;
	}

	FORCE_INLINE bool NearlyZero(float A, float Epsilon = EPSILON_FLOAT)
	{
		return A < Epsilon && A > -Epsilon;
	}

	FORCE_INLINE bool NearlyZero(double A, double Epsilon = EPSILON_DOUBLE)
	{
		return A < Epsilon && A > -Epsilon;
	}

	FORCE_INLINE float Interpolate(float A, float B, float T)
	{
		return A + (B - A) * T;
	}

	FORCE_INLINE double Interpolate(double A, double B, double T)
	{
		return A + (B - A) * T;
	}

	FORCE_INLINE Vector2f Interpolate(const Vector2f& VectorA, const Vector2f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	FORCE_INLINE Vector3f Interpolate(const Vector3f& VectorA, const Vector3f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	FORCE_INLINE Vector4f Interpolate(const Vector4f& VectorA, const Vector4f& VectorB, float T)
	{
		return VectorA + (VectorB - VectorA) * T;
	}

	FORCE_INLINE float Clamp(float Value, float Min, float Max)
	{
		return Value < Max ? (Value > Min ? Value : Min) : Max;
	}

	FORCE_INLINE double Clamp(double Value, double Min, double Max)
	{
		return Value < Max ? (Value > Min ? Value : Min) : Max;
	}

	FORCE_INLINE float Floor(float Value)
	{
		return floorf(Value);
	}

	FORCE_INLINE double Floor(double Value)
	{
		return floor(Value);
	}

	FORCE_INLINE float Ceil(float Value)
	{
		return ceilf(Value);
	}

	FORCE_INLINE double Ceil(double Value)
	{
		return ceil(Value);
	}

	FORCE_INLINE float Round(float Value)
	{
		return roundf(Value);
	}

	FORCE_INLINE double Round(double Value)
	{
		return round(Value);
	}

	template<typename TValue>
	FORCE_INLINE TValue Abs(TValue Value)
	{
		return Value < 0 ? -Value : Value;
	}

	template<typename TValue>
	FORCE_INLINE void Swap(TValue& A, TValue& B)
	{
		TValue Temp(A);
		A = std::move(B);
		B = std::move(Temp);
	}
}