#pragma once

#ifndef __SCENE__
#define __SCENE__

#include "RayTracer\Dependency\RayTracerDependency.h"
#include "RayTracer\Dependency\RayTracerMacro.h"

#include "Container\List\ArrayList.hpp"
#include "RayTracer\SceneToken.h"
#include "RayTracer\Object\Group.h"
#include "RayTracer\Object\IObject.h"
#include "RayTracer\Object\Plane.h"
#include "RayTracer\Object\Sphere.h"
#include "RayTracer\Object\Triangle.h"
#include "RayTracer\Object\TriangleMesh.h"
#include "RayTracer\Material\IMaterial.h"
#include "RayTracer\Material\BlinPhongMaterial.h"
#include "RayTracer\Material\PhongMaterial.h"
#include "RayTracer\Material\CookTorranceMaterial.h"
#include "RayTracer\Light\ILight.h"
#include "RayTracer\Light\DirectionalLight.h"
#include "RayTracer\Light\PointLight.h"
#include "RayTracer\Light\SpotLight.h"
#include "RayTracer\Camera\ICamera.h"
#include "RayTracer\Camera\OrthographicCamera.h"
#include "RayTracer\Camera\PerspectiveCamera.h"
#include "Tools\Json\json.hpp"

namespace EasyRayTracer
{

	class Scene
	{

	public:

		Scene(const String& FileName);

	private:

		void ParseBackground(nlohmann::json& BackgroundObject);
		void ParseCamera(nlohmann::json& CameraObject);
		void ParseLight(nlohmann::json& LightObject);
		void ParseMaterial(nlohmann::json& MaterialObject);
		void ParseGroup(nlohmann::json& GroupObject);

	private:

		void ParseOrthographicCamera(nlohmann::json& CameraObject);
		void ParsePerspectiveCamera(nlohmann::json& CameraObject);

		void ParseDirectionalLight(nlohmann::json& LightObject);
		void ParsePointLight(nlohmann::json& LightObject);
		void ParseSpotLight(nlohmann::json& LightObject);

		void ParsePhongMaterial(nlohmann::json& MaterialObject);
		void ParseBlinPhongMaterial(nlohmann::json& MaterialObject);
		void ParseCookTorranceMaterial(nlohmann::json& MaterialObject);

		void ParseSphere(nlohmann::json& GroupObject);
		void ParsePlane(nlohmann::json& GroupObject);
		void ParseTrianle(nlohmann::json& GroupObject);
		void ParseTrianleMesh(nlohmann::json& GroupObject);

	private:

		EasyMath::Vector3f ParseVector3f(String Text);
		float ParseFloat(String Text);
		int32 ParseInt(String Text);
		std::shared_ptr<EasyContainer::ArrayList<std::shared_ptr<Triangle>>> ParseObj(String FileName, std::shared_ptr<IMaterial> Material);

	private:

		std::shared_ptr<ICamera> m_Camera;
		std::shared_ptr<Group> m_Group;
		EasyContainer::ArrayList<std::shared_ptr<IMaterial>> m_Materials;
		EasyContainer::ArrayList<std::shared_ptr<ILight>> m_Lights;
		EasyMath::Vector3f m_AmbientColor;
		EasyMath::Vector3f m_BackgroundColor;
		nlohmann::json JsonParser;

	};

}

#endif