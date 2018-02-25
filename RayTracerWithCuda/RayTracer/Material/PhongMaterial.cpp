#include "stdafx.h"

#include "PhongMaterial.h"

namespace EasyRayTracer
{
	PhongMaterial::PhongMaterial(
		const EasyMath::Vector3f& ReflectionRate,
		const EasyMath::Vector3f& RefractionRate,
		const EasyMath::Vector3f& DiffuseCoefficiency, 
		const EasyMath::Vector3f& SpecularCoefficiency, 
		float Exponent, 
		float RefractiveIndex
	) :
		IMaterial(ReflectionRate, RefractionRate, RefractiveIndex),
		m_DiffuseCoefficiency(DiffuseCoefficiency),
		m_SpecularCoefficiency(SpecularCoefficiency),
		m_Exponent(Exponent)
	{

	}

	EasyMath::Color PhongMaterial::Ambient(const EasyMath::Vector3f& AmbientColor) const
	{
		EasyMath::Color Ambient = EasyMath::Color(
			m_DiffuseCoefficiency.X() * AmbientColor.X(),
			m_DiffuseCoefficiency.Y() * AmbientColor.Y(),
			m_DiffuseCoefficiency.Z() * AmbientColor.Z()
			);
		return Ambient;
	}

	EasyMath::Color PhongMaterial::Shade(
		const EasyMath::Vector3f& RayDirection, 
		const EasyMath::Vector3f& Normal, 
		const EasyMath::Vector3f& ColorLight,
		const EasyMath::Vector3f& ToLightDirection
	) const
	{
		EasyMath::Vector3f LightReflectiveOutDirection = EasyMath::Reflection(ToLightDirection.Negation(), Normal);
		EasyMath::Vector3f ViewDirection = RayDirection.Negation();

		float RDotV = EasyMath::Max(LightReflectiveOutDirection.Dot(ViewDirection), 0.0f);
		float NDotL = EasyMath::Max(Normal.Dot(ToLightDirection), 0.0f);

		float SpecularExponent = EasyMath::Pow(RDotV, m_Exponent);

		EasyMath::Color Color = EasyMath::Color(
			(NDotL * m_DiffuseCoefficiency.X() + SpecularExponent * m_SpecularCoefficiency.X()) * ColorLight.X(),
			(NDotL * m_DiffuseCoefficiency.Y() + SpecularExponent * m_SpecularCoefficiency.Y()) * ColorLight.Y(),
			(NDotL * m_DiffuseCoefficiency.Z() + SpecularExponent * m_SpecularCoefficiency.Z()) * ColorLight.Z()
			);

		return Color;
	}
}