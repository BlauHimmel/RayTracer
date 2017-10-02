#pragma once

#include "MathDependency.h"
#include "MathMacro.h"

namespace EasyMath
{

	class Matrix4f;
	class Vector4f;

	class Transform
	{

	public:

		static Matrix4f TranslationMatrix(float X, float Y, float Z);
		static Matrix4f ScaleMatrix(float X, float Y, float Z);
		static Matrix4f RotationMatrix(const Vector4f& Axis, float Angle);
		static Matrix4f IdentityMatrix();
		static Matrix4f ZeroMatrix();

	};

	Vector4f operator * (Matrix4f& Matrix, Vector4f& Vector);
	Vector4f operator * (Vector4f& Vector, Matrix4f& Matrix);
}