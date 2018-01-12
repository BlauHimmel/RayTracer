#pragma once

#ifndef __I_MATERIAL__
#define __I_MATERIAL__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"
#include "Math\Vector\Color.h"
#include "Math\Common\MathFunction.hpp"

namespace EasyRayTracer
{

	class IMaterial
	{

	public:

		IMaterial(const EasyMath::Vector3f& ReflectionRate, const EasyMath::Vector3f& RefractionRate);

	public:

		virtual EasyMath::Color Ambient(const EasyMath::Vector3f& AmbientColor) const = 0;

		virtual EasyMath::Color Shade(
			const EasyMath::Vector3f& RayDirection,
			const EasyMath::Vector3f& Normal,
			const EasyMath::Vector3f& ColorLight,
			const EasyMath::Vector3f& ToLightDirection
		) const = 0;

	protected:

		EasyMath::Vector3f m_ReflectionRate;
		EasyMath::Vector3f m_RefractionRate;
	
	};
}

#endif