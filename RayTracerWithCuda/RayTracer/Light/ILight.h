#pragma once

#ifndef __I_LIGHT__
#define __I_LIGHT__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class ILight
	{

	protected:

		float m_Intensity;
		EasyMath::Vector3f m_Color;

	public:

		ILight(float Intensity, const EasyMath::Vector3f& Color);

	public:

		virtual bool GetLight(
			const EasyMath::Vector3f& Position,
			EasyMath::Vector3f& Out_Color,
			EasyMath::Vector3f& Out_Direction,
			float& Out_Distance
		) const = 0;

	};
}

#endif