#pragma once

#ifndef __ORTHOGRAPHIC_CAMERA__
#define __ORTHOGRAPHIC_CAMERA__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Ray.h"
#include "RayTracer\Camera\ICamera.h"
#include "Math\Vector\Vector2f.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class OrthographicCamera : public ICamera
	{

	public:

		OrthographicCamera(
			const EasyMath::Vector3f& Origin,
			const EasyMath::Vector3f& Direction,
			const EasyMath::Vector3f& Up,
			float Size
		);

	public:

		virtual Ray GenerateRay(EasyMath::Vector2f Point) const override;
		virtual float TMin() const override;

	private:

		float m_Size;

	};
}

#endif