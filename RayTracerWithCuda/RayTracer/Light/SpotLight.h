#pragma once

#ifndef __SPOT_LIGHT__
#define __SPOT_LIGHT__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Light\PointLight.h"
#include "Math\Vector\Color.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class SpotLight : public PointLight
	{

	protected:

		float m_HalfAngle;
		EasyMath::Vector3f m_Direction;

	public:

		SpotLight(
			float Intensity,
			const EasyMath::Color& Color,
			const EasyMath::Vector3f& Position,
			float AttenuationCoefficiencyA,
			float AttenuationCoefficiencyB,
			float AttenuationCoefficiencyC,
			float Angle,
			EasyMath::Vector3f Direction
		);

	public:

		virtual bool GetLight(
			const EasyMath::Vector3f& Position,
			EasyMath::Color& Out_Color,
			EasyMath::Vector3f& Out_Direction,
			float& Out_Distance
		) const override;

	};
}

#endif