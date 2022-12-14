#include "Torus.h"


Torus::Torus(double radMid, double radIn, Vector3d pos, Color color, Vector3d norm) : Geometry(pos, color)
{
	_radiusIn = radIn;
	_radiusMid = radMid;
	_normal = norm;
}
Torus::~Torus()
{

}

CollisionResult Torus::intersect(const Vector3d& origin, const Vector3d& direction) const
{
	
}