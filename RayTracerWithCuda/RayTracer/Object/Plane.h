#pragma once

#ifndef __PLANE__
#define __PLANE__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Object\IObject.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class Plane : public IObject
	{

	public:

		Plane(std::shared_ptr<IMaterial> Material, EasyMath::Vector3f Normal, float Distance);

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const override;
		virtual void Draw() const override;

	private:

		EasyMath::Vector3f m_Normal;
		float m_Distance;
	};
}

#endif