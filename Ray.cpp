#pragma once

#include "Ray.h"




Ray::Ray(const Vector3d& origin, const Vector3d& direction)
{
	_origin = origin;
	_direction = direction;
	_direction.normalize();
}


Ray::~Ray(void)
{
}

bool Ray::checkIfLightBlocked(const std::vector<Geometry*>& tblGeo, const CollisionResult targetedGeo, double maxDistance) const
{
	for (size_t i = 1; i < tblGeo.size(); i++) // i = 0 normaly, its starting at 1 since 0 is the light which shouldnt block light-ray -- hack
	{
		if (static_cast<int>(i) != targetedGeo.index)
 		{
			CollisionResult tempResult = checkContactWithGeometry(*tblGeo[i]);
			if (tempResult.collided && tempResult.distance <= maxDistance)
			{
				return true;
			}
		}
	}
	return false;	
}

CollisionResult Ray::checkContactWithGeometry(const Geometry& geo) const
{
	return (geo.intersect(_origin, _direction));
}

Vector3d Ray::getDirectionToPoint(Vector3d point)
{
	return point - _origin;
}