#pragma once

#ifndef __TRIANGLE_MESH__
#define __TRIANGLE_MESH__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Object\IObject.h"
#include "RayTracer\Object\Triangle.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"
#include "Container\List\ArrayList.hpp"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class TriangleMesh : public IObject
	{

	public:

		TriangleMesh(
			std::shared_ptr<IMaterial> Material,
			EasyContainer::ArrayList<std::shared_ptr<Triangle>> Triangles
		);

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const override;
		virtual void Draw() const override;

	private:

		EasyContainer::ArrayList<std::shared_ptr<Triangle>> m_Triangles;

	};
}

#endif