#pragma once
#include "Geometry.h"
class Cylinder :
	public Geometry
{
private :
	Vector3d _axe; //Oz
	double _radius;
public : 
	Cylinder(const Vector3d& position, const Color& color, const Vector3d& axe, const double& rad);
	~Cylinder();
	CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const;
};

