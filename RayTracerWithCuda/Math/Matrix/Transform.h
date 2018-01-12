#pragma once

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "Math\Dependency\MathDependency.h"
#include "Math\Dependency\MathMacro.h"

#include "Math\Matrix\Transform.h"
#include "Math\Matrix\Matrix4f.h"
#include "Math\Vector\Vector4f.h"
#include "Math\Vector\Vector3f.h"

namespace EasyMath
{

	class Transform
	{

	public:

		static Matrix4f TranslationMatrix(float X, float Y, float Z);
		static Matrix4f ScaleMatrix(float X, float Y, float Z);
		static Matrix4f RotationMatrix(const Vector4f& Axis, float Angle);
		static Matrix4f IdentityMatrix();
		static Matrix4f ZeroMatrix();

		static Vector3f TransformPoint(const Vector3f& Point, const Matrix4f& Transform);
		static Vector3f TransformDirection(const Vector3f& Direction, const Matrix4f& Transform);

	};

	Vector4f operator * (const Matrix4f& Matrix, const Vector4f& Vector);
	Vector4f operator * (const Vector4f& Vector, const Matrix4f& Matrix);
}

#endif