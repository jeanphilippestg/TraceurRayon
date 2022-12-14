#pragma once
#include "Geometry.h"
#include "Plane.h"

class Square :
	public Geometry
{
public:
	Square(const Vector3d & norm, const Vector3d& width,const Vector3d& height,const Vector3d& position,const Color& color);
	~Square();
	virtual CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const override;
private : 
	Vector3d _normal;
	Vector3d _width;
	Vector3d _height;
	Plane *_plane;
};

