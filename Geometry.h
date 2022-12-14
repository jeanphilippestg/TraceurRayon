#pragma once
#include "UtilJP.h"

using namespace utilj;

class Geometry
{
protected:
	Vector3d _position;
	Color _color;
public :
	Geometry(const Vector3d & position, const Color & color);
	~Geometry(void);
	void moveTo(const Vector3d& position);
	void moveToward(const Vector3d& position);
	virtual CollisionResult intersect(const Vector3d& origin, const Vector3d& direction) const = 0;
};

 