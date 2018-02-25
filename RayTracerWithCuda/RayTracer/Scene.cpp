#include "stdafx.h"

#include "Scene.h"

namespace EasyRayTracer
{

	Scene::Scene(const String& FileName)
	{
		std::ifstream SceneFile(FileName, std::ios::in);
		SceneFile >> JsonParser;

		auto BackgroundObject = JsonParser[TOKEN_BACKGROUND];
		auto CameraObject = JsonParser[TOKEN_CAMERA];
		auto LightObject = JsonParser[TOKEN_LIGHT];
		auto MaterialObject = JsonParser[TOKEN_MATERIAL];
		auto GroupObject = JsonParser[TOKEN_GROUP];

		if (!BackgroundObject.is_null())
		{
			ParseBackground(BackgroundObject);
		}
		else
		{
			DEBUG_ERROR("Object Background Not Defined");
		}

		if (!CameraObject.is_null())
		{
			ParseCamera(CameraObject);
		}
		else
		{
			DEBUG_ERROR("Object Camera Not Defined");
		}

		if (!LightObject.is_null())
		{
			ParseLight(LightObject);
		}
		else
		{
			DEBUG_ERROR("Object Light Not Defined");
		}

		if (!MaterialObject.is_null())
		{
			ParseMaterial(MaterialObject);
		}
		else
		{
			DEBUG_ERROR("Object Material Not Defined");
		}

		if (!GroupObject.is_null())
		{
			ParseGroup(GroupObject);
		}
		else
		{
			DEBUG_ERROR("Object Group Not Defined");
		}
	}

	void Scene::DebugDraw()
	{
	}

	std::shared_ptr<ICamera> Scene::GetCamera()
	{
		return m_Camera;
	}

	std::shared_ptr<Group> Scene::GetGroup()
	{
		return m_Group;
	}

	int32 Scene::GetMaterialSize()
	{
		return m_Materials.Size();
	}

	int32 Scene::GetLightSize()
	{
		return m_Lights.Size();
	}

	std::shared_ptr<IMaterial> Scene::GetMaterial(int32 Index)
	{
		return m_Materials[Index];
	}

	std::shared_ptr<ILight> Scene::GetLight(int32 Index)
	{
		return m_Lights[Index];
	}

	EasyMath::Vector3f Scene::GetAmbientColor()
	{
		return m_AmbientColor;
	}

	EasyMath::Vector3f Scene::GetBackgroundColor()
	{
		return m_BackgroundColor;
	}

	void Scene::ParseBackground(nlohmann::json& BackgroundObject)
	{
		auto AmbientColor = BackgroundObject[TOKEN_BACKGROUND_AMBIENT_COLOR];
		auto BackgroundColor = BackgroundObject[TOKEN_BACKGROUND_BACKGROUND_COLOR];

		if (AmbientColor.is_null())
		{
			DEBUG_ERROR("Identifier AmbientColor Not Defined");
		}

		if (BackgroundColor.is_null())
		{
			DEBUG_ERROR("Identifier BackgroundColor Not Defined");
		}

		m_AmbientColor = ParseVector3f(AmbientColor);
		m_BackgroundColor = ParseVector3f(BackgroundColor);
	}

	void Scene::ParseCamera(nlohmann::json& CameraObject)
	{
		auto CameraType = CameraObject[TOKEN_TYPE];

		if (CameraType.is_null())
		{
			DEBUG_ERROR("Type Of Camera Is Not Defined");
		}

		if (CameraType == TOKEN_CAMERA_TYPE_ORTHOGRAPHIC)
		{
			ParseOrthographicCamera(CameraObject);
		}
		else if (CameraType == TOKEN_CAMERA_TYPE_PERSPECTIVE)
		{
			ParsePerspectiveCamera(CameraObject);
		}
		else
		{
			DEBUG_ERROR("Type Of Camera Is Invalid");
		}
	}

	void Scene::ParseLight(nlohmann::json& LightObject)
	{
		if (LightObject.size() > 0)
		{
			for (auto LightElement : LightObject)
			{
				auto LightType = LightElement[TOKEN_TYPE];

				if (LightType.is_null())
				{
					DEBUG_ERROR("Type Of Light Is Not Defined");
				}

				if (LightType == TOKEN_LIGHT_TYPE_DIRECTIONAL)
				{
					ParseDirectionalLight(LightElement);
				}
				else if (LightType == TOKEN_LIGHT_TYPE_POINT)
				{
					ParsePointLight(LightElement);
				}
				else if (LightType == TOKEN_LIGHT_TYPE_SPOT)
				{
					ParseSpotLight(LightElement);
				}
				else
				{
					DEBUG_ERROR("Type Of Light Is Invalid");
				}
			}
		}
	}

	void Scene::ParseMaterial(nlohmann::json& MaterialObject)
	{
		if (MaterialObject.size() > 0)
		{
			for (auto MaterialElement : MaterialObject)
			{
				auto MaterialType = MaterialElement[TOKEN_TYPE];

				if (MaterialType.is_null())
				{
					DEBUG_ERROR("Type Of Material Is Not Defined");
				}

				if (MaterialType == TOKEN_MATERIAL_TYPE_PHONG)
				{
					ParsePhongMaterial(MaterialElement);
				}
				else if (MaterialType == TOKEN_MATERIAL_TYPE_BLIN_PHONG)
				{
					ParseBlinPhongMaterial(MaterialElement);
				}
				else if (MaterialType == TOKEN_MATERIAL_TYPE_COOK_TORRANCE)
				{
					ParseCookTorranceMaterial(MaterialElement);
				}
				else
				{
					DEBUG_ERROR("Type Of Material Is Invalid");
				}
			}
		}
		else
		{
			DEBUG_ERROR("Object Material Is Null");
		}
	}

	void Scene::ParseGroup(nlohmann::json& GroupObject)
	{
		if (GroupObject.size() > 0)
		{
			m_Group = std::make_shared<Group>();

			for (auto GroupElement : GroupObject)
			{
				auto GroupType = GroupElement[TOKEN_TYPE];

				if (GroupType.is_null())
				{
					DEBUG_ERROR("Type Of Group Is Not Defined");
				}

				if (GroupType == TOKEN_GROUP_TYPE_SPHERE)
				{
					ParseSphere(GroupElement);
				}
				else if (GroupType == TOKEN_GROUP_TYPE_PLANE)
				{
					ParsePlane(GroupElement);
				}
				else if (GroupType == TOKEN_GROUP_TYPE_TRIANGLE)
				{
					ParseTrianle(GroupElement);
				}
				else if (GroupType == TOKEN_GROUP_TYPE_TRIANGLE_MESH)
				{
					ParseTrianleMesh(GroupElement);
				}
				else
				{
					DEBUG_ERROR("Type Of Group Is Invalid");
				}
			}
		}
		else
		{
			DEBUG_ERROR("Object Group Is Null");
		}
	}

	void Scene::ParseOrthographicCamera(nlohmann::json& CameraObject)
	{
		auto Origin = CameraObject[TOKEN_CAMERA_ORIGIN];
		auto Up = CameraObject[TOKEN_CAMERA_UP];
		auto Direction = CameraObject[TOKEN_CAMERA_DIRECTION];
		auto Size = CameraObject[TOKEN_CAMERA_SIZE];

		if (Origin.is_null())
		{
			DEBUG_ERROR("Origin Not Defined In Orthographic Camera");
		}

		if (Up.is_null())
		{
			DEBUG_ERROR("Up Not Defined In Orthographic Camera");
		}

		if (Direction.is_null())
		{
			DEBUG_ERROR("Direction Not Defined In Orthographic Camera");
		}

		if (Size.is_null())
		{
			DEBUG_ERROR("Size Not Defined In Orthographic Camera");
		}

		m_Camera = std::make_shared<OrthographicCamera>(
			ParseVector3f(Origin),
			ParseVector3f(Direction),
			ParseVector3f(Up),
			ParseFloat(Size)
			);
	}

	void Scene::ParsePerspectiveCamera(nlohmann::json& CameraObject)
	{
		auto Origin = CameraObject[TOKEN_CAMERA_ORIGIN];
		auto Up = CameraObject[TOKEN_CAMERA_UP];
		auto Direction = CameraObject[TOKEN_CAMERA_DIRECTION];
		auto FieldAngle = CameraObject[TOKEN_CAMERA_FIELD_ANGLE];

		if (Origin.is_null())
		{
			DEBUG_ERROR("Origin Not Defined In Perspective Camera");
		}

		if (Up.is_null())
		{
			DEBUG_ERROR("Up Not Defined In Perspective Camera");
		}

		if (Direction.is_null())
		{
			DEBUG_ERROR("Direction Not Defined In Perspective Camera");
		}

		if (FieldAngle.is_null())
		{
			DEBUG_ERROR("Field Angle Not Defined In Perspective Camera");
		}

		m_Camera = std::make_shared<PerspectiveCamera>(
			ParseVector3f(Origin),
			ParseVector3f(Direction),
			ParseVector3f(Up),
			ParseFloat(FieldAngle)
			);
	}

	void Scene::ParseDirectionalLight(nlohmann::json& LightObject)
	{
		auto Intensity = LightObject[TOKEN_LIGHT_INTENSITY];
		auto Color = LightObject[TOKEN_LIGHT_COLOR];
		auto Direction = LightObject[TOKEN_LIGHT_DIRECTION];

		if (Intensity.is_null())
		{
			DEBUG_ERROR("Intensity Not Defined In Directional Light");
		}

		if (Color.is_null())
		{
			DEBUG_ERROR("Color Not Defined In Directional Light");
		}

		if (Direction.is_null())
		{
			DEBUG_ERROR("Direction Not Defined In Directional Light");
		}

		m_Lights.Add(std::make_shared<DirectionalLight>(
			ParseFloat(Intensity),
			ParseVector3f(Color),
			ParseVector3f(Direction)
			));
	}

	void Scene::ParsePointLight(nlohmann::json& LightObject)
	{
		auto Intensity = LightObject[TOKEN_LIGHT_INTENSITY];
		auto Color = LightObject[TOKEN_LIGHT_COLOR];
		auto Position = LightObject[TOKEN_LIGHT_POSITION];
		auto Attenuation = LightObject[TOKEN_LIGHT_ATTENUATION];

		if (Intensity.is_null())
		{
			DEBUG_ERROR("Intensity Not Defined In Point Light");
		}

		if (Color.is_null())
		{
			DEBUG_ERROR("Color Not Defined In Point Light");
		}

		if (Position.is_null())
		{
			DEBUG_ERROR("Position Not Defined In Point Light");
		}

		if (Attenuation.is_null())
		{
			DEBUG_ERROR("Attenuation Not Defined In Point Light");
		}

		EasyMath::Vector3f AttenuationVec = ParseVector3f(Attenuation);

		m_Lights.Add(std::make_shared<PointLight>(
			ParseFloat(Intensity),
			ParseVector3f(Color),
			ParseVector3f(Position),
			AttenuationVec.X(),
			AttenuationVec.Y(),
			AttenuationVec.Z()
			));
	}

	void Scene::ParseSpotLight(nlohmann::json& LightObject)
	{
		auto Intensity = LightObject[TOKEN_LIGHT_INTENSITY];
		auto Color = LightObject[TOKEN_LIGHT_COLOR];
		auto Direction = LightObject[TOKEN_LIGHT_DIRECTION];
		auto Position = LightObject[TOKEN_LIGHT_POSITION];
		auto Attenuation = LightObject[TOKEN_LIGHT_ATTENUATION];
		auto Angle = LightObject[TOKEN_LIGHT_ANGLE];

		if (Intensity.is_null())
		{
			DEBUG_ERROR("Intensity Not Defined In Spot Light");
		}

		if (Color.is_null())
		{
			DEBUG_ERROR("Color Not Defined In Spot Light");
		}

		if (Direction.is_null())
		{
			DEBUG_ERROR("Direction Not Defined In Spot Light");
		}

		if (Position.is_null())
		{
			DEBUG_ERROR("Position Not Defined In Spot Light");
		}

		if (Attenuation.is_null())
		{
			DEBUG_ERROR("Attenuation Not Defined In Spot Light");
		}

		if (Angle.is_null())
		{
			DEBUG_ERROR("Angle Not Defined In Spot Light");
		}

		EasyMath::Vector3f AttenuationVec = ParseVector3f(Attenuation);

		m_Lights.Add(std::make_shared<SpotLight>(
			ParseFloat(Intensity),
			ParseVector3f(Color),
			ParseVector3f(Position),
			AttenuationVec.X(),
			AttenuationVec.Y(),
			AttenuationVec.Z(),
			ParseFloat(Angle),
			ParseVector3f(Direction)
			));
	}

	void Scene::ParsePhongMaterial(nlohmann::json& MaterialObject)
	{
		auto ReflectionRate = MaterialObject[TOKEN_MATERIAL_REFLECTION_RATE];
		auto RefractionRate = MaterialObject[TOKEN_MATERIAL_REFRACTION_RATE];
		auto DiffuseCoefficiency = MaterialObject[TOKEN_MATERIAL_DIFFUSE_COEFFICIENCY];
		auto SpecularCoefficiency = MaterialObject[TOKEN_MATERIAL_SPECULAR_COEFFICIENCY];
		auto Exponent = MaterialObject[TOKEN_MATERIAL_EXPONENT];
		auto RefractiveIndex = MaterialObject[TOKEN_MATERIAL_REFRACTIVE_INDEX];

		if (ReflectionRate.is_null())
		{
			DEBUG_ERROR("Reflection Rate Not Defined In Phong Material");
		}

		if (RefractionRate.is_null())
		{
			DEBUG_ERROR("Refraction Rate Not Defined In Phong Material");
		}

		if (DiffuseCoefficiency.is_null())
		{
			DEBUG_ERROR("Diffuse Coefficiency Not Defined In Phong Material");
		}

		if (SpecularCoefficiency.is_null())
		{
			DEBUG_ERROR("Specular Coefficiency Not Defined In Phong Material");
		}

		if (Exponent.is_null())
		{
			DEBUG_ERROR("Exponent Not Defined In Phong Material");
		}

		if (RefractiveIndex.is_null())
		{
			DEBUG_ERROR("Refractive Index Not Defined In Phong Material");
		}

		m_Materials.Add(std::make_shared<PhongMaterial>(
			ParseVector3f(ReflectionRate),
			ParseVector3f(RefractionRate),
			ParseVector3f(DiffuseCoefficiency),
			ParseVector3f(SpecularCoefficiency),
			ParseFloat(Exponent),
			ParseFloat(RefractiveIndex)
			));
	}

	void Scene::ParseBlinPhongMaterial(nlohmann::json& MaterialObject)
	{
		auto ReflectionRate = MaterialObject[TOKEN_MATERIAL_REFLECTION_RATE];
		auto RefractionRate = MaterialObject[TOKEN_MATERIAL_REFRACTION_RATE];
		auto DiffuseCoefficiency = MaterialObject[TOKEN_MATERIAL_DIFFUSE_COEFFICIENCY];
		auto SpecularCoefficiency = MaterialObject[TOKEN_MATERIAL_SPECULAR_COEFFICIENCY];
		auto Exponent = MaterialObject[TOKEN_MATERIAL_EXPONENT];
		auto RefractiveIndex = MaterialObject[TOKEN_MATERIAL_REFRACTIVE_INDEX];

		if (ReflectionRate.is_null())
		{
			DEBUG_ERROR("Reflection Rate Not Defined In Blin Phong Material");
		}

		if (RefractionRate.is_null())
		{
			DEBUG_ERROR("Refraction Rate Not Defined In Blin Phong Material");
		}

		if (DiffuseCoefficiency.is_null())
		{
			DEBUG_ERROR("Diffuse Coefficiency Not Defined In Blin Phong Material");
		}

		if (SpecularCoefficiency.is_null())
		{
			DEBUG_ERROR("Specular Coefficiency Not Defined In Blin Phong Material");
		}

		if (Exponent.is_null())
		{
			DEBUG_ERROR("Exponent Not Defined In Blin Phong Material");
		}

		if (RefractiveIndex.is_null())
		{
			DEBUG_ERROR("Refractive Index Not Defined In Blin Phong Material");
		}

		m_Materials.Add(std::make_shared<BlinPhongMaterial>(
			ParseVector3f(ReflectionRate),
			ParseVector3f(RefractionRate),
			ParseVector3f(DiffuseCoefficiency),
			ParseVector3f(SpecularCoefficiency),
			ParseFloat(Exponent),
			ParseFloat(RefractiveIndex)
			));
	}

	void Scene::ParseCookTorranceMaterial(nlohmann::json& MaterialObject)
	{
		auto ReflectionRate = MaterialObject[TOKEN_MATERIAL_REFLECTION_RATE];
		auto RefractionRate = MaterialObject[TOKEN_MATERIAL_REFRACTION_RATE];
		auto Albedo = MaterialObject[TOKEN_MATERIAL_ALBEDO];
		auto Metallic = MaterialObject[TOKEN_MATERIAL_METALLIC];
		auto Roughness = MaterialObject[TOKEN_MATERIAL_ROUGHNESS];
		auto Ao = MaterialObject[TOKEN_MATERIAL_AO];
		auto RefractiveIndex = MaterialObject[TOKEN_MATERIAL_REFRACTIVE_INDEX];

		if (ReflectionRate.is_null())
		{
			DEBUG_ERROR("Reflection Rate Not Defined In Cook Torrance Material");
		}

		if (RefractionRate.is_null())
		{
			DEBUG_ERROR("Refraction Rate Not Defined In Cook Torrance Material");
		}

		if (Albedo.is_null())
		{
			DEBUG_ERROR("Albedo Not Defined In Cook Torrance Material");
		}

		if (Metallic.is_null())
		{
			DEBUG_ERROR("Metallic Not Defined In Cook Torrance Material");
		}

		if (Roughness.is_null())
		{
			DEBUG_ERROR("Roughness Not Defined In Cook Torrance Material");
		}

		if (Ao.is_null())
		{
			DEBUG_ERROR("Ao Not Defined In Cook Torrance Material");
		}

		if (RefractiveIndex.is_null())
		{
			DEBUG_ERROR("Refractive Index Not Defined In Cook Torrance Material");
		}

		m_Materials.Add(std::make_shared<CookTorranceMaterial>(
			ParseVector3f(ReflectionRate),
			ParseVector3f(RefractionRate),
			ParseVector3f(Albedo),
			ParseFloat(Metallic),
			ParseFloat(Roughness),
			ParseFloat(Ao),
			ParseFloat(RefractiveIndex)
			));
	}

	void Scene::ParseSphere(nlohmann::json& GroupObject)
	{
		auto Center = GroupObject[TOKEN_GROUP_CENTER];
		auto Radius = GroupObject[TOKEN_GROUP_RADIUS];
		auto MaterialIndex = GroupObject[TOKEN_GROUP_MATERIAL_INDEX];

		if (Center.is_null())
		{
			DEBUG_ERROR("Center Not Defined In Sphere");
		}

		if (Radius.is_null())
		{
			DEBUG_ERROR("Center Not Defined In Sphere");
		}

		if (MaterialIndex.is_null())
		{
			DEBUG_ERROR("Material Index Not Defined In Sphere");
		}
		
		m_Group->Insert(std::make_shared<Sphere>(
			m_Materials[ParseInt(MaterialIndex)],
			ParseVector3f(Center),
			ParseFloat(Radius)
			));
	}

	void Scene::ParsePlane(nlohmann::json& GroupObject)
	{
		auto Normal = GroupObject[TOKEN_GROUP_NORMAL];
		auto Distance = GroupObject[TOKEN_GROUP_DISTANCE];
		auto MaterialIndex = GroupObject[TOKEN_GROUP_MATERIAL_INDEX];

		if (Normal.is_null())
		{
			DEBUG_ERROR("Normal Not Defined In Plane");
		}

		if (Distance.is_null())
		{
			DEBUG_ERROR("Distance Not Defined In Plane");
		}

		if (MaterialIndex.is_null())
		{
			DEBUG_ERROR("Material Index Not Defined In Plane");
		}

		m_Group->Insert(std::make_shared<Plane>(
			m_Materials[ParseInt(MaterialIndex)],
			ParseVector3f(Normal),
			ParseFloat(Distance)
			));
	}

	void Scene::ParseTrianle(nlohmann::json& GroupObject)
	{
		auto VertexA = GroupObject[TOKEN_GROUP_VERTEX_A];
		auto VertexB = GroupObject[TOKEN_GROUP_VERTEX_B];
		auto VertexC = GroupObject[TOKEN_GROUP_VERTEX_C];
		auto MaterialIndex = GroupObject[TOKEN_GROUP_MATERIAL_INDEX];

		if (VertexA.is_null())
		{
			DEBUG_ERROR("Vertex A Not Defined In Trianle");
		}

		if (VertexB.is_null())
		{
			DEBUG_ERROR("Vertex B Not Defined In Trianle");
		}

		if (VertexC.is_null())
		{
			DEBUG_ERROR("Vertex C Not Defined In Trianle");
		}

		if (MaterialIndex.is_null())
		{
			DEBUG_ERROR("Material Index Not Defined In Trianle");
		}

		m_Group->Insert(std::make_shared<Triangle>(
			m_Materials[ParseInt(MaterialIndex)],
			ParseVector3f(VertexA),
			ParseVector3f(VertexB),
			ParseVector3f(VertexC)
			));
	}

	void Scene::ParseTrianleMesh(nlohmann::json& GroupObject)
	{
		auto MaterialIndex = GroupObject[TOKEN_GROUP_MATERIAL_INDEX];
		auto FileName = GroupObject[TOKEN_GROUP_FILE_NAME];

		if (MaterialIndex.is_null())
		{
			DEBUG_ERROR("Material Index Not Defined In Trianle Mesh");
		} 

		if (FileName.is_null())
		{
			DEBUG_ERROR("File Name Not Defined In Trianle Mesh");
		}

		auto Triangles = ParseObj(FileName, m_Materials[ParseInt(MaterialIndex)]);

		for (auto Triangle : *Triangles)
		{
			m_Group->Insert(Triangle);
		}
	}

	EasyMath::Vector3f Scene::ParseVector3f(String Text)
	{
		std::istringstream Stream(Text);
		float X, Y, Z;
		Stream >> X >> Y >> Z;
		return EasyMath::Vector3f(X, Y, Z);
	}

	float Scene::ParseFloat(String Text)
	{
		std::istringstream Stream(Text);
		float Value;
		Stream >> Value;
		return Value;
	}

	int32 Scene::ParseInt(String Text)
	{
		std::istringstream Stream(Text);
		int32 Value;
		Stream >> Value;
		return Value;
	}

	std::shared_ptr<EasyContainer::ArrayList<std::shared_ptr<Triangle>>> Scene::ParseObj(String FileName, std::shared_ptr<IMaterial> Material)
	{
		std::shared_ptr<EasyContainer::ArrayList<std::shared_ptr<Triangle>>> Triangles(new EasyContainer::ArrayList<std::shared_ptr<Triangle>>());

		EasyContainer::ArrayList<EasyMath::Vector3f> Vertices;
		EasyContainer::ArrayList<int32> Indices;

		std::ifstream ObjFile(FileName, std::ios::in);
		if (!ObjFile.is_open())
		{
			DEBUG_ERROR("Obj File Not Exist");
		}

		while (!ObjFile.eof())
		{
			String Token;
			ObjFile >> Token;

			if (Token == TOKEN_OBJ_FILE_VERTEX)
			{
				float X, Y, Z;
				ObjFile >> X >> Y >> Z;
				Vertices.Add(EasyMath::Vector3f(X, Y, Z));
			}
			else if (Token == TOKEN_OBJ_FILE_FACET)
			{
				int32 IndexA, IndexB, IndexC;
				ObjFile >> IndexA >> IndexB >> IndexC;
				Indices.Add({ IndexA - 1, IndexB - 1, IndexC - 1 });
			}
		}

		for (auto i = 0; i < Indices.Size(); i += 3)
		{
			int32 IndexA = Indices[i];
			int32 IndexB = Indices[i + 1];
			int32 IndexC = Indices[i + 2];

			std::shared_ptr<Triangle> Primitive(new Triangle(Material, Vertices[IndexA], Vertices[IndexB], Vertices[IndexC]));
			Triangles->Add(Primitive);
		}

		ObjFile.close();

		return Triangles;
	}
}