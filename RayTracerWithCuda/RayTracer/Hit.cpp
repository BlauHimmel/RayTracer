#include "stdafx.h"

#include "Hit.h"

namespace EasyRayTracer
{

	Hit::Hit()
	{
		m_T = static_cast<float>(MAX_DISTANCE);
	}

	Hit::Hit(const Hit& Other)
	{
		m_T = Other.m_T;
		m_Normal = Other.m_Normal;
		m_Point = Other.m_Point;
		m_Material = Other.m_Material;
	}

	Hit::Hit(
		float T,
		const std::shared_ptr<IMaterial> Material,
		const EasyMath::Vector3f& Normal,
		const Ray& Ray) :
		m_T(T),
		m_Material(Material),
		m_Normal(Normal),
		m_Point(Ray.Point(T))
	{

	}

	void Hit::Set(
		float T, 
		const std::shared_ptr<IMaterial> Material,
		const EasyMath::Vector3f& Normal,
		const Ray& Ray
	)
	{
		m_T = T;
		m_Material = Material;
		m_Normal = Normal;
		m_Point = Ray.Point(T);
	}

	std::shared_ptr<IMaterial> Hit::Material() const
	{
		return m_Material;
	}

	float Hit::T() const
	{
		return m_T;
	}

	EasyMath::Vector3f Hit::Normal() const
	{
		return m_Normal;
	}

	EasyMath::Vector3f Hit::Point() const
	{
		return m_Point;
	}

	float& Hit::T()
	{
		return m_T;
	}

	EasyMath::Vector3f& Hit::Normal()
	{
		return m_Normal;
	}

	EasyMath::Vector3f& Hit::Point()
	{
		return m_Point;
	}
}