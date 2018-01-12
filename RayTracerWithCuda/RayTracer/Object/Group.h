#pragma once

#ifndef __GROUP__
#define __GROUP__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Object\IObject.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"
#include "Container\List\ArrayList.hpp"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class Group : public IObject
	{

	public:

		Group();

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const override;
		virtual void Draw() const override;

	public:

		void Insert(std::shared_ptr<IObject> Object);

	private:

		EasyContainer::ArrayList<std::shared_ptr<IObject>> m_Objects;

	};
}

#endif