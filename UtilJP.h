#pragma once
#include "Vector3.h"
#include "dugtga.h"


namespace utilj{
	
	typedef Pixel<octet> Color;

	struct CollisionResult // collided, distance, color, normal, intersection position, indexSphere
	{
		bool collided = false;
		double distance = 9999;
		Color color;
		Vector3d normal;
		Vector3d intersectionPosition;
		int index = -1;
	};



	
}

