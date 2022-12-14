#pragma once

//#include "UtilJP.h"
#include "Geometry.h"

using namespace utilj;

class Sphere : public Geometry
{
private:
	float _radius;
	float _radius2;
public:
	Sphere(const Vector3d& position, const float& radius,const Color& color);
	~Sphere(void);
	virtual CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const override;
};
