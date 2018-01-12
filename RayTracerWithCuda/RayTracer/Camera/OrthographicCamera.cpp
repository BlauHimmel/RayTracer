#include "stdafx.h"

#include "OrthographicCamera.h"

namespace EasyRayTracer
{

	OrthographicCamera::OrthographicCamera(
		const EasyMath::Vector3f& Origin, 
		const EasyMath::Vector3f& Direction, 
		const EasyMath::Vector3f& Up, 
		float Size
	) : 
		ICamera(Origin, Direction, Up),
		m_Size(Size)
	{

	}

	Ray OrthographicCamera::GenerateRay(EasyMath::Vector2f Point) const
	{
		EasyMath::Vector3f Origin = m_Origin + m_Horizontal * Point.X() * m_Size * 0.5f + m_Up * Point.Y() * m_Size * 0.5f;
		return Ray(Origin, m_Direction);
	}

	float OrthographicCamera::TMin() const
	{
		return -1.0f * INT_MAX;
	}
}