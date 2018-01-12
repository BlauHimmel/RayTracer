#include "stdafx.h"

#include "BlinPhongMaterial.h"

namespace EasyRayTracer
{
	BlinPhongMaterial::BlinPhongMaterial(
		const EasyMath::Vector3f& ReflectionRate,
		const EasyMath::Vector3f& RefractionRate,
		const EasyMath::Vector3f& DiffuseCoefficiency,
		const EasyMath::Vector3f& SpecularCoefficiency,
		float Exponent,
		float RefractiveIndex
	) :
		IMaterial(ReflectionRate, RefractionRate),
		m_DiffuseCoefficiency(DiffuseCoefficiency),
		m_SpecularCoefficiency(SpecularCoefficiency),
		m_Exponent(Exponent),
		m_RefractiveIndex(RefractiveIndex)
	{

	}

	EasyMath::Color BlinPhongMaterial::Ambient(const EasyMath::Vector3f& AmbientColor) const
	{
		EasyMath::Color Ambient = EasyMath::Color(
			m_DiffuseCoefficiency.X() * AmbientColor.X(),
			m_DiffuseCoefficiency.Y() * AmbientColor.Y(),
			m_DiffuseCoefficiency.Z() * AmbientColor.Z()
			);
			return Ambient;
	}

	EasyMath::Color BlinPhongMaterial::Shade(
		const EasyMath::Vector3f& RayDirection,
		const EasyMath::Vector3f& Normal,
		const EasyMath::Vector3f& ColorLight,
		const EasyMath::Vector3f& ToLightDirection
	) const
	{
		EasyMath::Vector3f LightReflectiveOutDirection = EasyMath::Reflection(ToLightDirection.Negation(), Normal);
		EasyMath::Vector3f HalfViewDirection = LightReflectiveOutDirection + RayDirection.Negation();
		HalfViewDirection.Normalize();

		float NDotH = EasyMath::Max(Normal.Dot(HalfViewDirection), 0.0f);
		float NDotL = EasyMath::Max(Normal.Dot(ToLightDirection), 0.0f);

		float SpecularExponent = EasyMath::Pow(NDotH, m_Exponent);

		EasyMath::Color Color = EasyMath::Color(
			(NDotL * m_DiffuseCoefficiency.X() + SpecularExponent * m_SpecularCoefficiency.X()) * ColorLight.X(),
			(NDotL * m_DiffuseCoefficiency.Y() + SpecularExponent * m_SpecularCoefficiency.Y()) * ColorLight.Y(),
			(NDotL * m_DiffuseCoefficiency.Z() + SpecularExponent * m_SpecularCoefficiency.Z()) * ColorLight.Z()
			);

			return Color;
	}
}