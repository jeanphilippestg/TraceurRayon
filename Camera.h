#pragma once
#include "Vector3.h"
#include "dugtga.h"
#include "ray.h"

class Camera
{
private:
	Vector3d _origin;
	float _scale;
	float _aspectRatio;
	float _fov;
	int _dimx;
	int _dimy;
public:
	Camera(const Vector3d & origin, const float & fov, const int & dimx, const int & dimy);
	~Camera(void);
	Ray buildRay(const int & posx, const int & posy);
	void moveCameraToward(const Vector3d & pos);
	Vector3i getDimension();

};
