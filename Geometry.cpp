#include "Geometry.h"


Geometry::Geometry(const Vector3d & position, const Color & color)
{
	_position = position;
	_color = color;
}

Geometry::~Geometry()
{

}

void Geometry::moveTo(const Vector3d& position) //for the sphere representing the light
{
	_position = position;
}
void Geometry::moveToward(const Vector3d& position)
{
	_position += position;
}