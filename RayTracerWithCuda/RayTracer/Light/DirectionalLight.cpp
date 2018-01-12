#include "stdafx.h"

#include "DirectionalLight.h"

namespace EasyRayTracer
{

	DirectionalLight::DirectionalLight(float Intensity, const EasyMath::Vector3f& Color, const EasyMath::Vector3f& Direction) :
		ILight(Intensity, Color), m_Direction(Direction)
	{
		m_Direction.Normalize();
	}

	bool DirectionalLight::GetLight(
		const EasyMath::Vector3f& Position,
		EasyMath::Vector3f& Out_Color,
		EasyMath::Vector3f& Out_Direction,
		float& Out_Distance
	) const
	{
		Out_Direction = m_Direction.Negation();
		Out_Distance = MAX_DISTANCE;
		Out_Color = m_Color * m_Intensity;
		return true;
	}
}