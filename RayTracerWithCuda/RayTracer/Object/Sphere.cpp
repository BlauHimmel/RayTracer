#include "stdafx.h"

#include "Sphere.h"

namespace EasyRayTracer
{

	Sphere::Sphere(std::shared_ptr<IMaterial> Material, EasyMath::Vector3f Center, float Radius) :
		IObject(Material),
		m_Center(Center),
		m_Radius(Radius)
	{

	}

	bool Sphere::Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const
	{
		bool IsIntersect = false;
		
		EasyMath::Vector3f Direction = Ray.Direction();
		EasyMath::Vector3f Origin = Ray.Origin();

		float A = Direction.Dot(Direction);
		float B = 2.0f * Direction.Dot(Origin - m_Center);
		float C = (Origin - m_Center).Length() * (Origin - (m_Center)).Length() - m_Radius * m_Radius;
		float Delta = B * B - 4.0f * A * C;
		float T = INT_MAX * 1.0f;

		if (Delta >= 0)
		{
			float Root = EasyMath::Sqrt(Delta);
			float DoubleA = 2.0f * A;
			float T1 = (-B - Root) / DoubleA;
			float T2 = (-B + Root) / DoubleA;

			if (T1 >= TMin)
			{
				T = T1;
				IsIntersect = true;
			}
			else if (T2 >= TMin)
			{
				T = T2;
				IsIntersect = true;
			}

			if (T < InOut_Hit.T())
			{
				EasyMath::Vector3f Normal = Origin + Direction * T - m_Center;
				Normal.Normalize();
				InOut_Hit.Set(T, m_Material, Normal, Ray);
			}
		}

		return IsIntersect;
	}
	
	void Sphere::Draw() const
	{
		//TODO:Use DirectX API Here To Draw The Primitive
	}
}
