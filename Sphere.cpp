#pragma once

#include "Sphere.h"

Sphere::Sphere(const Vector3d& position, const float& radius, const Color& color) : Geometry(position, color)
{
	_radius = radius;
	_radius2 = radius*radius;
}

Sphere::~Sphere(void)
{
}

const CollisionResult noCollision{ false, 9999 , {0,0,0}, {0,0,0}, {0,0,0}, 0 };

CollisionResult Sphere::intersect(const Vector3d & origin, const Vector3d & direction) const
{
	const Vector3d L = _position - origin; //direction : origin->sphere
	const double d{ L.produitScalaire(direction) }; //distance from origin to sphere
	const double lSqr{ L.produitScalaire(L) };
	if (((d >= 0) or (lSqr <= _radius2)))
	{
		const double mSqr = (lSqr - (d * d));
		if ((mSqr <= _radius2))
		{
			double t = 0;
			double q = sqrt((_radius2 - mSqr)); //lenght between intersection and middle of cirle
			if (lSqr > _radius2)
			{
				t = d - q;
			}
			else
			{
				t = d + q;
			}
			const Vector3d ptIntersect{ origin + (direction * t) };
			Vector3d normalIntersect{ ptIntersect - _position };
			normalIntersect.normalize();
			return { true, t, _color, normalIntersect, ptIntersect, 0 };
		}
	}
	return noCollision;
}