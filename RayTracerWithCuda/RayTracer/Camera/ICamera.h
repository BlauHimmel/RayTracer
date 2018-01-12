#pragma once

#ifndef __I_CAMERA__
#define __I_CAMERA__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Ray.h"
#include "Math\Vector\Vector2f.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class ICamera
	{

	public:

		ICamera(
			const EasyMath::Vector3f& Origin, 
			const EasyMath::Vector3f& Direction,
			const EasyMath::Vector3f& Up
		);

	public:

		virtual Ray GenerateRay(EasyMath::Vector2f Point) const = 0;
		virtual float TMin() const = 0;

	protected:

		EasyMath::Vector3f m_Origin;
		EasyMath::Vector3f m_Direction;
		EasyMath::Vector3f m_Horizontal;
		EasyMath::Vector3f m_Up;

	};
}

#endif