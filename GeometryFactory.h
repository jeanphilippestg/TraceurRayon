#pragma once
#include "Sphere.h"
#include "Plane.h"
#include "Square.h"
#include <sstream>
#include <vector>


class GeometryFactory
{


public : 
	GeometryFactory();
	~GeometryFactory( );
	void destroy(Geometry* pGeo);
	Geometry* BuildGeometry(std::string& command);
};

