#include "stdafx.h"

#include "ICamera.h"

namespace EasyRayTracer
{

	ICamera::ICamera(
		const EasyMath::Vector3f& Origin, 
		const EasyMath::Vector3f& Direction,
		const EasyMath::Vector3f& Up
	) :
		m_Origin(Origin),
		m_Direction(Direction),
		m_Up(Up)
	{
		m_Horizontal = m_Direction.Cross(m_Up);
		m_Up = m_Horizontal.Cross(m_Direction);

		m_Direction.Normalize();
		m_Up.Normalize();
		m_Horizontal.Normalize();
	}
}