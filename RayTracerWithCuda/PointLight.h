#pragma once

#include "RayTracerDependency.h"
#include "RayTracerMacro.h"

#include "ILight.h"
#include "Color.h"
#include "Vector3f.h"
#include "MathFunction.hpp"

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