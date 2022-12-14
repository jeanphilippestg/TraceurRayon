#pragma once
#include "Geometry.h"
class Triangle :
	public Geometry
{
public : 
	Triangle(Vector3d position, Color color);
		~Triangle();
		CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const;

};

