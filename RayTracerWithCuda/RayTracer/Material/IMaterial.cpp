#include "stdafx.h"

#include "IMaterial.h"

namespace EasyRayTracer
{
	IMaterial::IMaterial(
		const EasyMath::Vector3f& Reflection,
		const EasyMath::Vector3f& Refraction
	) : 
		m_ReflectionRate(Reflection),
		m_RefractionRate(Refraction)
	{

	}
}