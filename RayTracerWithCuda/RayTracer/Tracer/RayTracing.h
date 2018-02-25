#pragma once

#ifndef __RAY_CASTING__
#define __RAY_CASTING__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Scene.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Ray.h"
#include "Math\Common\MathFunction.hpp"
#include "Math\Vector\Vector3f.h"
#include "Math\Vector\Color.h"

namespace EasyRayTracer
{

	class RayTracing
	{

	public:

		RayTracing(std::shared_ptr<Scene> Scene, uint32 Bounce);

	public:

		EasyMath::Color Trace(const Ray& Ray, float TMin, uint32 Bounce, float RefractiveIndex);

	private:

		std::shared_ptr<Scene> m_Scene;
		uint32 m_Bounce;

	};
}

#endif