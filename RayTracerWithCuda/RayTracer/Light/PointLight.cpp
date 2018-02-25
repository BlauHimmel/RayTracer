#include "stdafx.h"

#include "PointLight.h"

namespace EasyRayTracer
{

	PointLight::PointLight(
		float Intensity, 
		const EasyMath::Vector3f& Color,
		const EasyMath::Vector3f& Position, 
		float AttenuationCoefficiencyA, 
		float AttenuationCoefficiencyB, 
		float AttenuationCoefficiencyC
	) : 
		ILight(Intensity, Color), 
		m_Position(Position),
		m_AttenuationCoefficiencyA(AttenuationCoefficiencyA), 
		m_AttenuationCoefficiencyB(AttenuationCoefficiencyB),
		m_AttenuationCoefficiencyC(AttenuationCoefficiencyC)
	{

	}

	bool PointLight::GetLight(
		const EasyMath::Vector3f& Position,
		EasyMath::Vector3f& Out_Color,
		EasyMath::Vector3f& Out_Direction,
		float& Out_Distance
	) const
	{
		Out_Direction = m_Position - Position;
		Out_Distance = Out_Direction.Length();
		Out_Direction.Normalize();
		float AttenuationCoefficiency = 1.0f / (
			m_AttenuationCoefficiencyA + 
			m_AttenuationCoefficiencyB * Out_Distance + 
			m_AttenuationCoefficiencyB * Out_Distance * Out_Distance
			);
		AttenuationCoefficiency = EasyMath::Max(AttenuationCoefficiency, 0.0f);
		Out_Color = m_Color * m_Intensity * AttenuationCoefficiency;
		return true;
	}
}