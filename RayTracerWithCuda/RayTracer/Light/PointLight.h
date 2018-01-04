#pragma once

#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Light\ILight.h"
#include "Math\Vector\Color.h"
#include "Math\Vector\Vector3f.h"
#include "Math\Common\MathFunction.hpp"

namespace EasyRayTracer
{

	class PointLight : public ILight
	{

	protected:

		EasyMath::Vector3f m_Position;
		float m_AttenuationCoefficiencyA, m_AttenuationCoefficiencyB, m_AttenuationCoefficiencyC;

	public:

		PointLight(
			float Intensity, 
			const EasyMath::Color& Color, 
			const EasyMath::Vector3f& Position,
			float AttenuationCoefficiencyA,
			float AttenuationCoefficiencyB,
			float AttenuationCoefficiencyC
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