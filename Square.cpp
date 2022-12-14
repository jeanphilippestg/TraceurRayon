#include "Square.h"

Square::Square(const Vector3d& norm, const Vector3d& width, const Vector3d& height, const Vector3d& position, const Color& color) : Geometry(position, color)
{
	_normal = norm;
	_width = width;
	_height = height;
	_plane = new Plane { _position,_color, _normal };
}

Square::~Square()
{
}
const CollisionResult noCollision{ false, 9999 , {0,0,0}, {0,0,0}, {0,0,0}, 0 };

CollisionResult Square::intersect(const Vector3d& origin, const Vector3d& direction) const
{
	const CollisionResult cr{ _plane->intersect(origin, direction) };
	const Vector3d P{ cr.intersectionPosition - _position };
	if (cr.collided && P.x >= 0 && P.x <= _width.x && P.y >= 0 && P.y <= _height.y)
	{
		return cr;
	}
	return noCollision;
}