#pragma once

#ifndef __SCENE_TOKEN__
#define __SCENE_TOKEN__

#define TOKEN_TYPE "Type"

#define TOKEN_BACKGROUND "Background"
#define TOKEN_BACKGROUND_AMBIENT_COLOR "AmbientColor"
#define TOKEN_BACKGROUND_BACKGROUND_COLOR "BackgroundColor"

#define TOKEN_CAMERA "Camera"
#define TOKEN_CAMERA_ORIGIN "Origin"
#define TOKEN_CAMERA_UP "Up"
#define TOKEN_CAMERA_DIRECTION "Direction"
#define TOKEN_CAMERA_FIELD_ANGLE "FieldAngle"
#define TOKEN_CAMERA_SIZE "Size"
#define TOKEN_CAMERA_TYPE_PERSPECTIVE "PerspectiveCamera"
#define TOKEN_CAMERA_TYPE_ORTHOGRAPHIC "OrthographicCamera"

#define TOKEN_LIGHT "Light"
#define TOKEN_LIGHT_INTENSITY "Intensity"
#define TOKEN_LIGHT_COLOR "Color"
#define TOKEN_LIGHT_POSITION "Position"
#define TOKEN_LIGHT_DIRECTION "Direction"
#define TOKEN_LIGHT_ATTENUATION "Attenuation"
#define TOKEN_LIGHT_ANGLE "Angle"
#define TOKEN_LIGHT_TYPE_POINT "PointLight"
#define TOKEN_LIGHT_TYPE_DIRECTIONAL "DirectionalLight"
#define TOKEN_LIGHT_TYPE_SPOT "SpotLight"

#define TOKEN_MATERIAL "Material"
#define TOKEN_MATERIAL_REFLECTION_RATE "ReflectionRate"
#define TOKEN_MATERIAL_REFRACTION_RATE "RefractionRate"
#define TOKEN_MATERIAL_DIFFUSE_COEFFICIENCY "DiffuseCoefficiency"
#define TOKEN_MATERIAL_SPECULAR_COEFFICIENCY "SpecularCoefficiency"
#define TOKEN_MATERIAL_EXPONENT "Exponent"
#define TOKEN_MATERIAL_REFRACTIVE_INDEX "RefractiveIndex"
#define TOKEN_MATERIAL_ALBEDO "Albedo"
#define TOKEN_MATERIAL_METALLIC "Metallic"
#define TOKEN_MATERIAL_ROUGHNESS "Roughness"
#define TOKEN_MATERIAL_AO "Ao"
#define TOKEN_MATERIAL_TYPE_BLIN_PHONG "BlinPhongMaterial"
#define TOKEN_MATERIAL_TYPE_PHONG "PhongMaterial"
#define TOKEN_MATERIAL_TYPE_COOK_TORRANCE "CookTorranceMaterial"

#define TOKEN_GROUP "Group"
#define TOKEN_GROUP_MATERIAL_INDEX "MaterialIndex"
#define TOKEN_GROUP_CENTER "Center"
#define TOKEN_GROUP_RADIUS "Radius"
#define TOKEN_GROUP_NORMAL "Normal"
#define TOKEN_GROUP_DISTANCE "Distance"
#define TOKEN_GROUP_VERTEX_A "VertexA"
#define TOKEN_GROUP_VERTEX_B "VertexB"
#define TOKEN_GROUP_VERTEX_C "VertexC"
#define TOKEN_GROUP_FILE_NAME "FileName"
#define TOKEN_GROUP_TYPE_SPHERE "Sphere"
#define TOKEN_GROUP_TYPE_TRIANGLE "Triangle"
#define TOKEN_GROUP_TYPE_PLANE "Plane"
#define TOKEN_GROUP_TYPE_TRIANGLE_MESH "TriangleMesh"

#define TOKEN_OBJ_FILE_VERTEX "v"
#define TOKEN_OBJ_FILE_FACET "f"

#endif