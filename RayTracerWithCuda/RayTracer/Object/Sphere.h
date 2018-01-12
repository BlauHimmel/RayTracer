#pragma once

#ifndef __SPHERE__
#define __SPHERE__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Object\IObject.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"
#include "Math\Vector\Vector3f.h"
#include "Math\Common\MathFunction.hpp"

namespace EasyRayTracer
{

	class Sphere : public IObject
	{

	public:

		Sphere(std::shared_ptr<IMaterial> Material, EasyMath::Vector3f Center, float Radius);

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const override;
		virtual void Draw() const override;

	private:

		EasyMath::Vector3f m_Center;
		float m_Radius;
	};
}

#endif