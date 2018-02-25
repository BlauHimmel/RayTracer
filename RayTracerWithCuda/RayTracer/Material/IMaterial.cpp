#include "stdafx.h"

#include "IMaterial.h"

namespace EasyRayTracer
{
	IMaterial::IMaterial(
		const EasyMath::Vector3f& ReflectionRate,
		const EasyMath::Vector3f& RefractionRate,
		float RefractiveIndex
	) : 
		m_ReflectionRate(ReflectionRate),
		m_RefractionRate(RefractionRate),
		m_RefractiveIndex(RefractiveIndex)
	{

	}

	bool IMaterial::IsReflective() const
	{
		return m_ReflectionRate.Length() != 0;
	}

	bool IMaterial::IsRefractive() const
	{
		return m_RefractionRate.Length() != 0;
	}

	EasyMath::Vector3f IMaterial::ReflectionRate() const
	{
		return m_ReflectionRate;
	}
	
	EasyMath::Vector3f IMaterial::RefractionRate() const
	{
		return m_RefractionRate;
	}
	
	float IMaterial::RefractiveIndex()
	{
		return m_RefractiveIndex;
	}
}