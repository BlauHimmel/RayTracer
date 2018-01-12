#include "stdafx.h"

#include "CookTorranceMaterial.h"

namespace EasyRayTracer
{

	CookTorranceMaterial::CookTorranceMaterial(
		const EasyMath::Vector3f& ReflectionRate,
		const EasyMath::Vector3f& RefractionRate,
		const EasyMath::Vector3f& Albedo,
		float Metallic,
		float Roughness,
		float Ao
	) :
		IMaterial(ReflectionRate, RefractionRate),
		m_Albedo(Albedo),
		m_Metallic(Metallic),
		m_Roughness(Roughness),
		m_Ao(Ao)
	{

	}

	EasyMath::Color CookTorranceMaterial::Ambient(const EasyMath::Vector3f& AmbientColor) const
	{
		EasyMath::Color Ambient = EasyMath::Color(
			0.03f * m_Albedo.X() * m_Ao * AmbientColor.X(),
			0.03f * m_Albedo.Y() * m_Ao * AmbientColor.Y(),
			0.03f * m_Albedo.Z() * m_Ao * AmbientColor.Z()
			);

		Ambient = EasyMath::Color(
			EasyMath::Pow(Ambient.R() / (Ambient.R() + 1.0f), 1.0f / 2.2f),
			EasyMath::Pow(Ambient.G() / (Ambient.G() + 1.0f), 1.0f / 2.2f),
			EasyMath::Pow(Ambient.B() / (Ambient.B() + 1.0f), 1.0f / 2.2f)
		);

		return Ambient;
	}

	EasyMath::Color CookTorranceMaterial::Shade(
		const EasyMath::Vector3f& RayDirection, 
		const EasyMath::Vector3f& Normal, 
		const EasyMath::Vector3f& ColorLight,
		const EasyMath::Vector3f& ToLightDirection
	) const
	{
		EasyMath::Vector3f LightReflectiveOutDirection = EasyMath::Reflection(ToLightDirection.Negation(), Normal);
		EasyMath::Vector3f HalfViewDirection = LightReflectiveOutDirection + RayDirection.Negation();
		HalfViewDirection.Normalize();
		EasyMath::Vector3f ViewDirection = RayDirection.Negation();
		EasyMath::Vector3f F0 = EasyMath::Vector3f(0.04f, 0.04f, 0.04f);
		F0 = EasyMath::Interpolate(F0, m_Albedo, m_Metallic);
		float HDotV = EasyMath::Max(HalfViewDirection.Dot(ViewDirection), 0.0f);
		float NDotV = EasyMath::Max(Normal.Dot(ViewDirection), 0.0f);
		float NDotL = EasyMath::Max(Normal.Dot(ToLightDirection), 0.0f);

		float D = DistributionGGX(Normal, HalfViewDirection, m_Roughness);
		EasyMath::Vector3f F = FresnelSchlick(HDotV, F0);
		float G = GeometrySmith(Normal, ViewDirection, ToLightDirection, m_Roughness);

		EasyMath::Vector3f SpecularCoefficiency = F;
		EasyMath::Vector3f DiffuseCoefficiency = EasyMath::Vector3f(
			1.0f - SpecularCoefficiency.X(), 
			1.0f - SpecularCoefficiency.Y(), 
			1.0f - SpecularCoefficiency.Z()
		);
		DiffuseCoefficiency *= (1.0 - m_Metallic);
        
		EasyMath::Vector3f Numerator = D * G * F;
        float Denominator = 4.0 * NDotV * NDotL;

		EasyMath::Vector3f Specular = Numerator / EasyMath::Max(Denominator, 0.001F);
                         
		EasyMath::Color Color = EasyMath::Color(
			((DiffuseCoefficiency.X() * m_Albedo.X()) / PI + Specular.X()) * NDotL * ColorLight.X(),
			((DiffuseCoefficiency.Y() * m_Albedo.Y()) / PI + Specular.Y()) * NDotL * ColorLight.Y(),
			((DiffuseCoefficiency.Z() * m_Albedo.Z()) / PI + Specular.Z()) * NDotL * ColorLight.Z()
		);

		Color = EasyMath::Color(
			EasyMath::Pow(Color.R() / (Color.R() + 1.0f), 1.0f / 2.2f),
			EasyMath::Pow(Color.G() / (Color.G() + 1.0f), 1.0f / 2.2f),
			EasyMath::Pow(Color.B() / (Color.B() + 1.0f), 1.0f / 2.2f)
		);

		return Color;
	}

	float CookTorranceMaterial::DistributionGGX(
		const EasyMath::Vector3f& Normal,
		const EasyMath::Vector3f& HalfViewDirection, 
		float Roughness
	) const
	{
		float A = Roughness * Roughness;
		float A2 = A * A;

		float NdotH = EasyMath::Max(Normal.Dot(HalfViewDirection), 0.0f);
		float NdotH2 = NdotH * NdotH;

		float Numerator = A2;
		float Denominator = NdotH2 * (A2 - 1.0) + 1.0;
		Denominator = PI * Denominator * Denominator;

		return Numerator / Denominator;
	}

	float CookTorranceMaterial::GeometrySchlickGGX(float NDotV, float Roughness) const
	{
		float R = Roughness + 1.0;
		float K = (R * R) / 8.0;

		float Numerator = NDotV;
		float Denominator = NDotV * (1.0 - K) + K;

		return Numerator / Denominator;
	}

	float CookTorranceMaterial::GeometrySmith(
		const EasyMath::Vector3f& Normal,
		const EasyMath::Vector3f& ViewDirection,
		const EasyMath::Vector3f& ToLightDirection,
		float Roughness
	) const
	{
		float NdotV = EasyMath::Max(Normal.Dot(ViewDirection), 0.0f);
		float NdotL = EasyMath::Max(Normal.Dot(ToLightDirection), 0.0f);
		float GGX2 = GeometrySchlickGGX(NdotV, Roughness);
		float GGX1 = GeometrySchlickGGX(NdotL, Roughness);

		return GGX1 * GGX2;
	}

	EasyMath::Vector3f CookTorranceMaterial::FresnelSchlick(float CosTheta, const EasyMath::Vector3f& F0) const
	{
		return F0 + EasyMath::Vector3f(1.0f - F0.X(), 1.0f - F0.Y(), 1.0f - F0.Z()) * EasyMath::Pow(1.0f - CosTheta, 5.0f);
	}
}