#include "stdafx.h"

#include "Group.h"

namespace EasyRayTracer
{

	Group::Group() : IObject(std::shared_ptr<IMaterial>())
	{

	}

	bool Group::Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const
	{
		bool IsIntersect = false;
		for (std::shared_ptr<IObject> Object : m_Objects)
		{
			if (Object->Intersect(Ray, TMin, InOut_Hit))
			{
				IsIntersect = true;
			}
		}
		return IsIntersect;
	}

	void Group::Draw() const
	{
		for (std::shared_ptr<IObject> Object : m_Objects)
		{
			Object->Draw();
		}
	}

	void Group::Insert(std::shared_ptr<IObject> Object)
	{
		m_Objects.Add(Object);
	}

}