#pragma once

#ifndef __MATH_FUNCTION__
#define __MATH_FUNCTION__

#include "Math\Dependency\MathDependency.h"
#include "Math\Dependency\MathMacro.h"

#include "Math\Vector\Vector2f.h"
#include "Math\Vector\Vector3f.h"
#include "Math\Vector\Vector4f.h"

namespace EasyMath
{

	/**
	* ������������ķ���
	* @param InDirection:��������ķ�������
	* @param Normal:���ʽ��紦�ķ�����
	* @param InRefractionCoefficiency:��������������ʵ�����ϵ��
	* @param OutRefractionCoefficiency:��������������ʵ�����ϵ��
	* @return OutDirection:������ߵķ�������
	*/
	INLINE Vector3f Refraction(
		const Vector3f& InDirection, 
		const Vector3f& Normal, 
		float CoefficiencyRatio)
	{
		//[ ��r (N �� I) �C ��(1 �C ��r^2 (1 �C(N �� I)^2)) ] N �C ��r I
		//��r = ��i / ��o
		
		float NormalDotInComing = Normal.Dot(-InDirection);

		Vector3f OutDirection = (
			CoefficiencyRatio * NormalDotInComing - 
			sqrtf(1.0f - CoefficiencyRatio * CoefficiencyRatio * (1.0f - NormalDotInComing * NormalDotInComing))
			) * Normal - CoefficiencyRatio * InDirection;
		OutDirection.Normalize();
		return OutDirection;
	}

	/**
	* ������߷����ķ���
	* @param InDirection:��������ķ�������
	* @param Normal:���ʽ��紦�ķ�����
	* @return OutDirection:������ߵķ�������
	*/
	INLINE Vector3f Reflection(const Vector3f& InDirection, const Vector3f& Normal)
	{
		//I �C 2 (I �� N) N

		Vector3f OutDirection = InDirection - 2.0f * InDirection.Dot(Normal) * Normal;
		OutDirection.Normalize();
		return OutDirection;
	}

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

	FORCE_INLINE void ClampRef(float& Value, float Min, float Max)
	{
		Value = Value < Max ? (Value > Min ? Value : Min) : Max;
	}

	FORCE_INLINE void ClampRef(double& Value, double Min, double Max)
	{
		Value = Value < Max ? (Value > Min ? Value : Min) : Max;
	}

	FORCE_INLINE float Floor(float Value)
	{
		return floorf(Value);
	}

	FORCE_INLINE double Floor(double Value)
	{
		return floor(Value);
	}

	FORCE_INLINE void FloorRef(float& Value)
	{
		Value = floorf(Value);
	}

	FORCE_INLINE void FloorRef(double& Value)
	{
		Value = floor(Value);
	}

	FORCE_INLINE float Ceil(float Value)
	{
		return ceilf(Value);
	}

	FORCE_INLINE double Ceil(double Value)
	{
		return ceil(Value);
	}

	FORCE_INLINE void CeilRef(float& Value)
	{
		Value = ceilf(Value);
	}

	FORCE_INLINE void CeilRef(double& Value)
	{
		Value = ceil(Value);
	}

	FORCE_INLINE float Round(float Value)
	{
		return roundf(Value);
	}

	FORCE_INLINE double Round(double Value)
	{
		return round(Value);
	}

	FORCE_INLINE void RoundRef(float& Value)
	{
		Value = roundf(Value);
	}

	FORCE_INLINE void RoundRef(double& Value)
	{
		Value = round(Value);
	}

	FORCE_INLINE float Sin(float Value)
	{
		return sinf(Value);
	}

	FORCE_INLINE double Sin(double Value)
	{
		return sin(Value);
	}

	FORCE_INLINE float Cos(float Value)
	{
		return cosf(Value);
	}

	FORCE_INLINE double Cos(double Value)
	{
		return cos(Value);
	}

	FORCE_INLINE float Tan(float Value)
	{
		return tanf(Value);
	}

	FORCE_INLINE double Tan(double Value)
	{
		return tan(Value);
	}

	FORCE_INLINE float ArcSin(float Value)
	{
		return asinf(Value);
	}

	FORCE_INLINE double ArcSin(double Value)
	{
		return asin(Value);
	}

	FORCE_INLINE float ArcCos(float Value)
	{
		return acosf(Value);
	}

	FORCE_INLINE double ArcCos(double Value)
	{
		return acos(Value);
	}

	FORCE_INLINE float ArcTan(float Value)
	{
		return atanf(Value);
	}

	FORCE_INLINE double ArcTan(double Value)
	{
		return atan(Value);
	}

	FORCE_INLINE float Pow(float Base, float Power)
	{
		return powf(Base, Power);
	}

	FORCE_INLINE double Pow(double Base, double Power)
	{
		return pow(Base, Power);
	}

	FORCE_INLINE float Sqrt(float Value)
	{
		return sqrtf(Value);
	}

	FORCE_INLINE double Sqrt(double Value)
	{
		return sqrt(Value);
	}

	template<typename TValue>
	FORCE_INLINE TValue Max(TValue ValueA, TValue ValueB)
	{
		return ValueA > ValueB ? ValueA : ValueB;
	}

	template<typename TValue>
	FORCE_INLINE TValue Min(TValue ValueA, TValue ValueB)
	{
		return ValueA > ValueB ? ValueB : ValueA;
	}

	template<typename TValue>
	FORCE_INLINE TValue Abs(TValue Value)
	{
		return Value < 0 ? -Value : Value;
	}

	template<typename TValue>
	FORCE_INLINE void AbsRef(TValue& Value)
	{
		Value = Value < 0 ? -Value : Value;
	}

	template<typename TValue>
	FORCE_INLINE void Swap(TValue& A, TValue& B)
	{
		TValue Temp(A);
		A = std::move(B);
		B = std::move(Temp);
	}
}

#endif