#pragma once
#include "Geometry.h"
class Torus :
	public Geometry
{
public :
	Torus(double radMid, double radIn, Vector3d pos, Color color, Vector3d norm);
	~Torus();
	
private :
	double _radiusMid;
	double _radiusIn;
	Vector3d _normal;

	virtual CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const override;
};

