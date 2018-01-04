#pragma once

#ifndef __I_MATERIAL__
#define __I_MATERIAL__

#include "RayTracerDependency.h"
#include "RayTracerMacro.h"

#include "Vector3f.h"
#include "Color.h"
#include "Ray.h"
#include "Hit.h"

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