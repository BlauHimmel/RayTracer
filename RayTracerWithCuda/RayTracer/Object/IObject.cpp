#include "stdafx.h"

#include "IObject.h"

namespace EasyRayTracer
{

	IObject::IObject(std::shared_ptr<IMaterial> Material) : m_Material(Material)
	{

	}
}