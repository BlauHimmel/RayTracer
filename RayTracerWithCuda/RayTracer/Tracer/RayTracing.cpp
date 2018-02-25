#include "stdafx.h"

#include "RayTracing.h"

namespace EasyRayTracer
{

	RayTracing::RayTracing(std::shared_ptr<Scene> Scene, uint32 Bounce)
	{
		m_Scene = Scene;
		m_Bounce = Bounce;
	}

	EasyMath::Color RayTracing::Trace(const Ray& InRay, float TMin, uint32 Bounce, float RefractiveIndex)
	{
		std::shared_ptr<Group> Group = m_Scene->GetGroup();
		int32 LightSize = m_Scene->GetLightSize();
		EasyMath::Vector3f BackgroundColor = m_Scene->GetBackgroundColor();
		EasyMath::Vector3f AmbientColor = m_Scene->GetAmbientColor();

		Hit GroupHit;

		if (!Group->Intersect(InRay, TMin, GroupHit))
		{
			return EasyMath::Color(BackgroundColor.X(), BackgroundColor.Y(), BackgroundColor.Z());
		}

		std::shared_ptr<IMaterial> Material = GroupHit.Material();
		EasyMath::Color Pixel = Material->Ambient(AmbientColor);;
		EasyMath::Vector3f Normal = GroupHit.Normal();
		EasyMath::Vector3f Point = GroupHit.Point();
		
		for (auto i = 0; i < LightSize; i++)
		{
			std::shared_ptr<ILight> Light = m_Scene->GetLight(i);

			EasyMath::Vector3f ToLightDirection;
			EasyMath::Vector3f ColorLight;
			float LightDistance;

			if (!Light->GetLight(Point, ColorLight, ToLightDirection, LightDistance))
			{
				continue;
			}

			Ray ShadowRay = Ray(Point, ToLightDirection);
			Hit ShadowHit;
			ShadowHit.T() = LightDistance;

			if (Group->Intersect(ShadowRay, TMin, ShadowHit))
			{
				continue;
			}

#ifdef SHADE_BACKFACE
			if (InRay.Direction().Dot(Normal) > 0)
			{
				Normal.Negate();
			}
#endif 

			Pixel += Material->Shade(InRay.Direction(), Normal, ColorLight, ToLightDirection);

#ifdef SHADE_BACKFACE
			if (InRay.Direction().Dot(Normal) > 0)
			{
				Normal.Negate();
			}
#endif 
		}

		if (Bounce <= m_Bounce)
		{
			if (Material->IsReflective())
			{
				EasyMath::Vector3f ReflectiveDirection = EasyMath::Reflection(InRay.Direction(), Normal);

				Ray ReflectiveRay = Ray(Point, ReflectiveDirection);
				Hit ReflectiveHit;

				EasyMath::Color ReflectiveColor = Trace(ReflectiveRay, TMin, Bounce + 1, RefractiveIndex);
				ReflectiveColor *= Material->ReflectionRate();

				Pixel += ReflectiveColor;
			}

			if (Material->IsRefractive())
			{
				float MaterialRefractiveIndex = Material->RefractiveIndex();
				float Rate = RefractiveIndex / MaterialRefractiveIndex;

				if (InRay.Direction().Dot(Normal) > 0)
				{
					Normal.Negate();
					Rate = 1.0f / Rate;
				}

				EasyMath::Vector3f RefractiveDirection = EasyMath::Refraction(InRay.Direction(), Normal, Rate);

				Ray RefractiveRay = Ray(Point, RefractiveDirection);
				Hit RefractiveHit;

				EasyMath::Color RefractiveColor = Trace(RefractiveRay, TMin, Bounce + 1, RefractiveIndex);
				RefractiveColor *= Material->RefractionRate();
			
				Pixel += RefractiveColor;
			}
		}

		return Pixel;
	}
}