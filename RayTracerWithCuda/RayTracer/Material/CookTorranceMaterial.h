#pragma once

#ifndef __COOK_TORRANCE_MATERIAL__
#define __COOK_TORRANCE_MATERIAL__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"
#include "RayTracer\Material\IMaterial.h"

namespace EasyRayTracer
{

	class CookTorranceMaterial : public IMaterial
	{

	public:

		CookTorranceMaterial(
			const EasyMath::Vector3f& ReflectionRate,
			const EasyMath::Vector3f& RefractionRate,
			const EasyMath::Vector3f& Albedo,
			float Metallic,
			float Roughness,
			float Ao
		);

	public:

		virtual EasyMath::Color Ambient(const EasyMath::Vector3f& AmbientColor) const override;

		virtual EasyMath::Color Shade(
			const EasyMath::Vector3f& RayDirection,
			const EasyMath::Vector3f& Normal,
			const EasyMath::Vector3f& ColorLight,
			const EasyMath::Vector3f& ToLightDirection
		) const override;

	private:

		float DistributionGGX(
			const EasyMath::Vector3f& Normal,
			const EasyMath::Vector3f& HalfViewDirection,
			float Roughness
		) const;

		float GeometrySchlickGGX(float NDotV, float Roughness) const;

		float GeometrySmith(
			const EasyMath::Vector3f& Normal,
			const EasyMath::Vector3f& ViewDirection,
			const EasyMath::Vector3f& ToLightDirection,
			float Roughness
		) const;

		EasyMath::Vector3f FresnelSchlick(float CosTheta, const EasyMath::Vector3f& F0) const;

	private:

		EasyMath::Vector3f m_Albedo;
		float m_Metallic;
		float m_Roughness;
		float m_Ao;

	};
}

#endif