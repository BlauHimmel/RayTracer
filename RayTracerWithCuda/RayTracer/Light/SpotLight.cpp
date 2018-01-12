#include "stdafx.h"

#include "SpotLight.h"

namespace EasyRayTracer
{

	SpotLight::SpotLight(
		float Intensity,
		const EasyMath::Vector3f& Color,
		const EasyMath::Vector3f& Position, 
		float AttenuationCoefficiencyA, 
		float AttenuationCoefficiencyB, 
		float AttenuationCoefficiencyC,
		float Angle,
		EasyMath::Vector3f Direction
	) : 
		PointLight(Intensity, Color, Position, AttenuationCoefficiencyA, AttenuationCoefficiencyB, AttenuationCoefficiencyC),
		m_HalfAngle(0.5f * Angle),
		m_Direction(Direction)
	{
		m_Direction.Normalize();
	}

	bool SpotLight::GetLight(
		const EasyMath::Vector3f& Position,
		EasyMath::Vector3f& Out_Color,
		EasyMath::Vector3f& Out_Direction,
		float& Out_Distance
	) const
	{
		Out_Direction = m_Position - Position;
		Out_Direction.Normalize();
		
		if (EasyMath::ArcCos(Out_Direction.Dot(m_Direction.Negation())) <= m_HalfAngle)
		{
			Out_Distance = Out_Direction.Length();
			float AttenuationCoefficiency = 1.0f / (
				m_AttenuationCoefficiencyA +
				m_AttenuationCoefficiencyB * Out_Distance +
				m_AttenuationCoefficiencyB * Out_Distance * Out_Distance
				);
			AttenuationCoefficiency = EasyMath::Max(AttenuationCoefficiency, 0.0f);
			Out_Color = m_Color * m_Intensity * AttenuationCoefficiency;
			return true;
		}
		else
		{
			Out_Direction = EasyMath::Vector3f();
			Out_Color = EasyMath::Vector3f();
			Out_Distance = MAX_DISTANCE;
			return false;
		}
	}
}