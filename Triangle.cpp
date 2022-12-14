#include "Triangle.h"


Triangle::Triangle(Vector3d position, Color color) : Geometry(position, color)
{

}

Triangle::~Triangle()
{

}

CollisionResult Triangle::intersect(const Vector3d& origin, const Vector3d& direction) const
{
	
}