#include "stdafx.h"

#include "ILight.h"

namespace EasyRayTracer
{

	ILight::ILight(float Intensity, const EasyMath::Vector3f& Color) : m_Intensity(Intensity), m_Color(Color)
	{

	}
}