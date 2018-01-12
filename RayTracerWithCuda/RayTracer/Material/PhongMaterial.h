#pragma once

#ifndef __PHONG_MATERIAL__
#define __PHONG_MATERIAL__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"
#include "RayTracer\Material\IMaterial.h"

namespace EasyRayTracer
{

	class PhongMaterial : public IMaterial
	{

	public:

		PhongMaterial(
			const EasyMath::Vector3f& ReflectionRate,
			const EasyMath::Vector3f& RefractionRate,
			const EasyMath::Vector3f& DiffuseCoefficiency,
			const EasyMath::Vector3f& SpecularCoefficiency,
			float Exponent,
			float RefractiveIndex
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

		EasyMath::Vector3f m_DiffuseCoefficiency;
		EasyMath::Vector3f m_SpecularCoefficiency;
		float m_Exponent;
		float m_RefractiveIndex;

	};
}

#endif