#include "stdafx.h"

#include "Ray.h"

namespace EasyRayTracer
{

	Ray::Ray()
	{

	}

	Ray::Ray(const EasyMath::Vector3f Origin, const EasyMath::Vector3f Direction) :
		m_Origin(Origin),
		m_Direction(Direction)
	{

	}

	Ray::Ray(const Ray& Other)
	{
		this->m_Origin = Other.m_Origin;
		this->m_Direction = Other.m_Direction;
	}

	EasyMath::Vector3f Ray::Origin() const
	{
		return m_Origin;
	}

	EasyMath::Vector3f Ray::Direction() const
	{
		return m_Direction;
	}

	EasyMath::Vector3f& Ray::Origin()
	{
		return m_Origin;
	}

	EasyMath::Vector3f& Ray::Direction()
	{
		return m_Direction;
	}

	EasyMath::Vector3f Ray::Point(float T) const
	{
		return EasyMath::Vector3f(
			m_Origin.X() + m_Direction.X() * T,
			m_Origin.Y() + m_Direction.Y() * T,
			m_Origin.Z() + m_Direction.Z() * T
		);
	}
}