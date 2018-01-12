#include "stdafx.h"

#include "PerspectiveCamera.h"

namespace EasyRayTracer
{

	PerspectiveCamera::PerspectiveCamera(
		const EasyMath::Vector3f& Origin, 
		const EasyMath::Vector3f& Direction, 
		const EasyMath::Vector3f& Up, 
		float FieldAngle
	) :
		ICamera(Origin, Direction, Up),
		m_FieldAngle(FieldAngle)
	{
		m_Distance = 1.0f / EasyMath::Tan(FieldAngle / 2.0f);
	}

	Ray PerspectiveCamera::GenerateRay(EasyMath::Vector2f Point) const
	{
		EasyMath::Vector3f Direction = m_Horizontal * Point.X() + m_Up * Point.Y() + m_Direction * m_Distance;
		Direction.Normalize();
		return Ray(m_Origin, Direction);
	}

	float PerspectiveCamera::TMin() const
	{
		return 0.0f;
	}
}