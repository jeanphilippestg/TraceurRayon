#include "Camera.h"

Camera::Camera(const Vector3d& origin, const float& fov, const int& dimx, const int& dimy)
{
	_origin = origin;
	_scale = tan(fov / 2 * 3.1415926535f / 180.f);
	_aspectRatio = dimx / (float)dimy;
	_fov = fov;
	_dimx = dimx;
	_dimy = dimy;
}
Camera::~Camera(void)
{}

Ray Camera::buildRay(const int& posx, const int& posy)
{
	float px = (2.f * ((posx + 0.5f) / _dimx) - 1) * _scale * _aspectRatio;
	float py = (1.f - 2 * ((posy + 0.5f) / _dimy)) * _scale;
	return Ray{ _origin, {px, py, 1} };
}

void Camera:: moveCameraToward(const Vector3d& pos)
{
	_origin += pos;
}

Vector3i Camera::getDimension()
{
	return { _dimx, _dimy, 0 };
}