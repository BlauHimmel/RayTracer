#include "stdafx.h"

#include "Triangle.h"

namespace EasyRayTracer
{

	Triangle::Triangle(
		std::shared_ptr<IMaterial> Material,
		EasyMath::Vector3f VertexA,
		EasyMath::Vector3f VertexB,
		EasyMath::Vector3f VertexC
	) :
		IObject(Material),
		m_VertexA(VertexA),
		m_VertexB(VertexB),
		m_VertexC(VertexC),
		m_EdgeA(VertexB - VertexA),
		m_EdgeB(VertexC - VertexA),
		m_Normal(m_EdgeA.Cross(m_EdgeB))
	{
		
	}

	bool Triangle::Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const
	{
		bool IsIntersect = false;

		EasyMath::Vector3f L = Ray.Origin() - m_VertexA;
		EasyMath::Vector3f K = Ray.Direction().Negation();
		float Det = K.Dot(m_Normal);

#ifdef CULLING_BACKFACE
		if (Det < 0)
		{
			return false;
		}
#endif

		if (Det != 0)
		{
			float DetT = L.Dot(m_Normal);
			EasyMath::Vector3f T1 = L.Cross(m_EdgeB);
			EasyMath::Vector3f T2 = m_EdgeA.Cross(L);

			float DetU = K.Dot(T1);
			float DetV = K.Dot(T2);

			float T = DetT / Det;
			float U = DetU / Det;
			float V = DetV / Det;

			if (T > TMin && U >= 0 && V >= 0 && 1 - U - V >= 0 && T < InOut_Hit.T())
			{
				IsIntersect = true;
				InOut_Hit.Set(T, m_Material, m_Normal.Normal(), Ray);
			}
		}
		
		return IsIntersect;
	}

	void Triangle::Draw() const
	{
		//TODO:Use DirectX API Here To Draw The Primitive
	}
}