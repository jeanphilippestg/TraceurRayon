#include "Light.h"


Light::Light(Vector3d pos)
{
	_position = pos;
}

Light::~Light()
{

}

Vector3d& Light::getLightPosition()
{
	return _position;
}