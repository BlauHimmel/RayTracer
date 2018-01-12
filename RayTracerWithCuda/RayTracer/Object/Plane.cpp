#include "stdafx.h"

#include "Plane.h"

namespace EasyRayTracer
{

	Plane::Plane(std::shared_ptr<IMaterial> Material, EasyMath::Vector3f Normal, float Distance) :
		IObject(Material),
		m_Normal(Normal),
		m_Distance(Distance)
	{
		m_Normal.Normalize();
	}

	bool Plane::Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const
	{
		bool IsIntersect = false;

		float NDotDir = m_Normal.Dot(Ray.Direction());
		
		if (NDotDir == 0)
		{
			IsIntersect = false;
		}
		else
		{
			float T = (m_Distance - m_Normal.Dot(Ray.Origin())) / NDotDir;
			if (T >= TMin && T < InOut_Hit.T())
			{
				IsIntersect = true;
				InOut_Hit.Set(T, m_Material, m_Normal, Ray);
			}
		}
		return IsIntersect;
	}

	void Plane::Draw() const
	{
		//TODO:Use DirectX API Here To Draw The Primitive
	}
}
