#pragma once
#include "Geometry.h"

class Plane :
	public Geometry
{
private:
	Vector3d _normal;
public :
	Plane(const Vector3d& position, const Color& color, const Vector3d& norm);
	~Plane();
	virtual CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const override;
};

