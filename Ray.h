#pragma once

#include "Sphere.h"
#include <vector>

class Ray
{
private : 
	Vector3d _origin;
	Vector3d _direction;
public :
	Ray(const Vector3d& origin, const Vector3d& direction);
	~Ray(void);
	CollisionResult checkContactWithGeometry(const Geometry& geo) const;
	bool checkIfLightBlocked(const std::vector<Geometry*>& tblGeo, const CollisionResult targetedGeo, double maxDistance) const;
	Vector3d getDirectionToPoint(Vector3d point);
};
