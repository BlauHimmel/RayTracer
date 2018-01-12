#pragma once

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Object\IObject.h"
#include "RayTracer\Ray.h"
#include "RayTracer\Hit.h"
#include "RayTracer\Material\IMaterial.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class Triangle : public IObject
	{

	public:

		Triangle(
			std::shared_ptr<IMaterial> Material, 
			EasyMath::Vector3f VertexA, 
			EasyMath::Vector3f VertexB, 
			EasyMath::Vector3f VertexC
		);

	public:

		virtual bool Intersect(const Ray& Ray, float TMin, Hit& InOut_Hit) const override;
		virtual void Draw() const override;

	private:

		EasyMath::Vector3f m_VertexA;
		EasyMath::Vector3f m_VertexB;
		EasyMath::Vector3f m_VertexC;
		EasyMath::Vector3f m_EdgeA;
		EasyMath::Vector3f m_EdgeB;
		EasyMath::Vector3f m_Normal;
	};
}

#endif