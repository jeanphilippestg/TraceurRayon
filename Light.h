#pragma once
#include "Vector3.h"
class Light
{
public:
	Light(Vector3d pos);
	~Light();
	Vector3d& getLightPosition();
private : 
	Vector3d _position;
};

