#include "stdafx.h"

#include "TriangleMesh.h"

namespace EasyRayTracer
{

	TriangleMesh::TriangleMesh(
		std::shared_ptr<IMaterial> Material,
		EasyContainer::ArrayList<std::shared_ptr<Triangle>> Triangles
	) :
		IObject(Material),
		m_Triangles(Triangles)
	{

	}

	bool TriangleMesh::Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const
	{
		bool IsIntersect = false;
		for (std::shared_ptr<Triangle> Triangle : m_Triangles)
		{
			if (Triangle->Intersect(Ray, TMin, InOut_Hit))
			{
				IsIntersect = true;
			}
		}
		return IsIntersect;
	}

	void TriangleMesh::Draw() const
	{
		for (std::shared_ptr<Triangle> Triangle : m_Triangles)
		{
			Triangle->Draw();
		}
	}
}