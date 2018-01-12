#pragma once

#ifndef __RAY__
#define __RAY__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class Ray
	{

	public:

		Ray();
		Ray(const EasyMath::Vector3f Origin, const EasyMath::Vector3f Direction);
		Ray(const Ray& Other);

	public:

		EasyMath::Vector3f Origin() const;
		EasyMath::Vector3f Direction() const;
		EasyMath::Vector3f& Origin();
		EasyMath::Vector3f& Direction();
		EasyMath::Vector3f Point(float T) const;

	private:

		EasyMath::Vector3f m_Origin;
		EasyMath::Vector3f m_Direction;

	};
}

#endif