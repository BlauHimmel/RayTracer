#pragma once

#ifndef __I_MATERIAL__
#define __I_MATERIAL__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"
#include "Math\Vector\Color.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"

namespace EasyRayTracer
{

	class IMaterial
	{
		virtual EasyMath::Vector3f Shade(
			const Ray& Ray,
			const Hit& Hit,
			EasyMath::Color& Light,
			EasyMath::Vector3f& LightDirection
			) const = 0;
	
	};
}

#endif