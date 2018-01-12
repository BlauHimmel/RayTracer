#include "stdafx.h"

#include "Transform.h"

namespace EasyMath
{

	Matrix4f Transform::TranslationMatrix(float X, float Y, float Z)
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			Ret.m_Data[Row][Row] = 1.0f;
		}
		Ret.m_Data[3][0] = X;
		Ret.m_Data[3][1] = Y;
		Ret.m_Data[3][2] = Z;
		return Ret;
	}

	Matrix4f Transform::ScaleMatrix(float X, float Y, float Z)
	{
		Matrix4f Ret;
		Ret.m_Data[0][0] = X;
		Ret.m_Data[1][1] = Y;
		Ret.m_Data[2][2] = Z;
		Ret.m_Data[3][3] = 1.0f;
		return Ret;
	}

	Matrix4f Transform::RotationMatrix(const Vector4f& Axis, float Theta)
	{
		Matrix4f Ret;

		float HalfTheta = Theta * 0.5f;
		float SinHalfTheta = sinf(HalfTheta);
		float CosHalfTheta = cosf(HalfTheta);
		Vector4f AxisNormal = Axis.Normal();

		float X = AxisNormal.m_X * SinHalfTheta;
		float Y = AxisNormal.m_Y * SinHalfTheta;
		float Z = AxisNormal.m_Z * SinHalfTheta;
		float W = CosHalfTheta;

		float X2 = X * X; float Y2 = Y * Y; float Z2 = Z * Z;
		float XY = X * Y; float XZ = X * Z; float YZ = Y * Z;
		float XW = X * W; float YW = Y * W; float ZW = Z * W;

		Ret.m_Data[0][0] = 1 - 2 * (Y2 + Z2);
		Ret.m_Data[1][0] = 2 * (XY - ZW);
		Ret.m_Data[2][0] = 2 * (XZ + YW);
		Ret.m_Data[3][0] = 0.0f;

		Ret.m_Data[0][1] = 2 * (XY + ZW);
		Ret.m_Data[1][1] = 1 - 2 * (X2 + Z2);
		Ret.m_Data[2][1] = 2 * (YZ - XW);
		Ret.m_Data[3][1] = 0.0f;

		Ret.m_Data[0][2] = 2 * (XZ - YW);
		Ret.m_Data[1][2] = 2 * (YZ + XW);
		Ret.m_Data[2][2] = 1 - 2 * (X2 + Y2);
		Ret.m_Data[3][2] = 0.0f;

		Ret.m_Data[0][3] = 0.0f;
		Ret.m_Data[1][3] = 0.0f;
		Ret.m_Data[2][3] = 0.0f;
		Ret.m_Data[3][3] = 1.0f;

		return Ret;
	}

	Matrix4f Transform::IdentityMatrix()
	{
		Matrix4f Ret;
		for (auto Row = 0; Row < 4; Row++)
		{
			Ret.m_Data[Row][Row] = 1.0f;
		}
		return Ret;
	}

	Matrix4f Transform::ZeroMatrix()
	{
		return Matrix4f();
	}

	Vector3f Transform::TransformPoint(const Vector3f& Point, const Matrix4f& Transform)
	{
		Vector4f Home = Vector4f(Point.X(), Point.Y(), Point.Z(), 1.0f);
		Home = Home * Transform;
		return Vector3f(Home.X(), Home.Y(), Home.Z());
	}

	Vector3f Transform::TransformDirection(const Vector3f& Direction, const Matrix4f& Transform)
	{
		Vector4f Home = Vector4f(Direction.X(), Direction.Y(), Direction.Z(), 0.0f);
		Home = Home * Transform;
		return Vector3f(Home.X(), Home.Y(), Home.Z());
	}

	Vector4f operator * (const Vector4f& Vector, const Matrix4f& Matrix)
	{
		float X = Vector.X() * Matrix(0, 0) + Vector.Y() * Matrix(1, 0) + Vector.Z() * Matrix(2, 0) + Vector.W() * Matrix(3, 0);
		float Y = Vector.X() * Matrix(0, 1) + Vector.Y() * Matrix(1, 1) + Vector.Z() * Matrix(2, 1) + Vector.W() * Matrix(3, 1);
		float Z = Vector.X() * Matrix(0, 2) + Vector.Y() * Matrix(1, 2) + Vector.Z() * Matrix(2, 2) + Vector.W() * Matrix(3, 2);
		float W = Vector.X() * Matrix(0, 3) + Vector.Y() * Matrix(1, 3) + Vector.Z() * Matrix(2, 3) + Vector.W() * Matrix(3, 3);
		return Vector4f(X, Y, Z, W);
	}

	Vector4f operator * (const Matrix4f& Matrix, const Vector4f& Vector)
	{
		float X = Vector.X() * Matrix(0, 0) + Vector.Y() * Matrix(0, 1) + Vector.Z() * Matrix(0, 2) + Vector.W() * Matrix(0, 3);
		float Y = Vector.X() * Matrix(1, 0) + Vector.Y() * Matrix(1, 1) + Vector.Z() * Matrix(1, 2) + Vector.W() * Matrix(1, 3);
		float Z = Vector.X() * Matrix(2, 0) + Vector.Y() * Matrix(2, 1) + Vector.Z() * Matrix(2, 2) + Vector.W() * Matrix(2, 3);
		float W = Vector.X() * Matrix(3, 0) + Vector.Y() * Matrix(3, 1) + Vector.Z() * Matrix(3, 2) + Vector.W() * Matrix(3, 3);
		return Vector4f(X, Y, Z, W);
	}
}
