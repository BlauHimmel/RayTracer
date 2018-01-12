#pragma once

#ifndef __HIT__
#define __HIT__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "RayTracer\Ray.h"
#include "RayTracer\Material\IMaterial.h"
#include "Math\Vector\Vector3f.h"

namespace EasyRayTracer
{

	class Hit
	{

	public:

		Hit();
		Hit(const Hit& Other);
		Hit(
			float T, 
			const std::shared_ptr<IMaterial> Material,
			const EasyMath::Vector3f& Normal,
			const Ray& Ray
		);

	public:

		void Set(
			float T,
			const std::shared_ptr<IMaterial> Material,
			const EasyMath::Vector3f& Normal,
			const Ray& Ray
		);

		std::shared_ptr<IMaterial> Material() const;

		float T() const;
		EasyMath::Vector3f Normal() const;
		EasyMath::Vector3f Point() const;

		float& T();
		EasyMath::Vector3f& Normal();
		EasyMath::Vector3f& Point();

	private:

		float m_T;
		std::shared_ptr<IMaterial> m_Material;
		EasyMath::Vector3f m_Normal;
		EasyMath::Vector3f m_Point;

	};
}

#endif