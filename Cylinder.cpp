#include "Cylinder.h"

Cylinder::Cylinder(const Vector3d& position, const Color& color, const Vector3d& axe, const double& rad) : Geometry(position, color)
{
	_axe = axe;
	_radius = rad;
}

Cylinder::~Cylinder()
{

}

CollisionResult Cylinder::intersect(const Vector3d& origin, const Vector3d& direction) const
{
	Vector3d L = origin - _position;
	Vector3d w = direction.produitVectoriel(_axe);
	double wsquared = w.produitScalaire(w);
	if (wsquared == 0)
	{
		//double a = L.produitScalaire(_axe);
	//double t = -b
	}
	return { true, 0, _color,{}, {},0 };
}