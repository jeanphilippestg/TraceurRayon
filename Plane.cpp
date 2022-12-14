#include "Plane.h"

Plane::Plane(const Vector3d& position, const Color& color, const Vector3d & norm) : Geometry(position, color)
{
	_position = position;
	_color = color;
	_normal = norm;
	_normal.normalize();
}

Plane::~Plane()
{}

const CollisionResult noCollision{ false, 9999 , {0,0,0}, {0,0,0}, {0,0,0}, 0 };

CollisionResult Plane::intersect(const Vector3d& origin, const Vector3d& direction) const
{
	const double m = _normal.produitScalaire(direction);
	if (abs(m) >= 1e-4)
	{
		//const double t = (_position - origin).produitScalaire(_normal) / m;
		const Vector3d L = origin - _position;
		const double d = _normal.produitScalaire(L);
		const double t = (-d / m);
		if (t > 0)
		{
			return { true, t, _color, _normal, origin + (direction*t), 0 };
		}
	}
	return noCollision;
}