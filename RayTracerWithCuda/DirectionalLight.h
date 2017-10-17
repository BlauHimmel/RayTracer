#pragma once

#include "RayTracerDependency.h"
#include "RayTracerMacro.h"

#include "ILight.h"
#include "Color.h"
#include "Vector3f.h"

namespace EasyRayTracer
{

	class DirectionalLight : public ILight
	{

	protected:

		EasyMath::Vector3f m_Direction;

	public:

		DirectionalLight(float Intensity, const EasyMath::Color& Color, const EasyMath::Vector3f& Direction);

	public:

		virtual bool GetLight(
			const EasyMath::Vector3f& Position,
			EasyMath::Color& Out_Color,
			EasyMath::Vector3f& Out_Direction,
			float& Out_Distance
		) const override;

	};
}