#pragma once

#ifndef __I_OBJECT__
#define __I_OBJECT__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"

namespace EasyRayTracer
{

	class IObject
	{

	public:

		IObject(std::shared_ptr<IMaterial> Material);

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const = 0;
		virtual void Draw() const = 0;

	protected:
		
		std::shared_ptr<IMaterial> m_Material;

	};
}

#endif