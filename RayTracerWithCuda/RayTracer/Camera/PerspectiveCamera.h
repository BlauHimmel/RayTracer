#pragma once

#ifndef __PERSPECTIVE_CAMERA__
#define __PERSPECTIVE_CAMERA__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Ray.h"
#include "RayTracer\Camera\ICamera.h"
#include "Math\Vector\Vector2f.h"
#include "Math\Vector\Vector3f.h"
#include "Math\Common\MathFunction.hpp"

namespace EasyRayTracer
{

	class PerspectiveCamera : public ICamera
	{

	public:

		PerspectiveCamera(
			const EasyMath::Vector3f& Origin,
			const EasyMath::Vector3f& Direction,
			const EasyMath::Vector3f& Up,
			float FieldAngle
		);

	public:

		virtual Ray GenerateRay(EasyMath::Vector2f Point) const override;
		virtual float TMin() const override;

	private:

		float m_FieldAngle;
		float m_Distance;

	};
}

#endif