#pragma once

#ifndef __I_LIGHT__
#define __I_LIGHT__

#include "RayTracerDependency.h"
#include "RayTracerMacro.h"

#include "Color.h"
#include "Vector3f.h"

namespace EasyRayTracer
{

	class ILight
	{

	protected:

		float m_Intensity;
		EasyMath::Color m_Color;

	public:

		ILight(float Intensity, const EasyMath::Color& Color);

	public:

		virtual bool GetLight(
			const EasyMath::Vector3f& Position,
			EasyMath::Color& Out_Color,
			EasyMath::Vector3f& Out_Direction,
			float& Out_Distance
		) const = 0;

	};
}

#endif