#pragma once

#include "MathDependency.h"
#include "MathMacro.h"



namespace EasyMath
{
	class Vector4f;
	class Matrix4f;

	class Transform
	{

	public:

		static Matrix4f GetTranslationMatrix(float X, float Y, float Z);
		static Matrix4f GetScaleMatrix(float X, float Y, float Z);
		static Matrix4f GetRotationMatrix(const Vector4f& Axis, float Angle);

	public:

		friend Matrix4f operator 

	};
}