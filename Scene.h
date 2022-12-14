#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "UtilJP.h"
#include "Camera.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Square.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "GeometryFactory.h"
#include "Light.h"


using namespace utilj;

class Scene
{
private:
	Color _color{};
	std::vector<Geometry*> _tblGeo;
	Camera* _pCam;
	Light* _light;
	GeometryFactory _geoFactory;
public:
	Scene(std::ifstream& file);
	~Scene(void);
	Color returnColorToUse(const int& x, const int& y);
	void moveAllSphere(const int& frame);
	void moveCameraToward(const Vector3d& pos);
	Vector3i getDimension();
	bool addGeometry(std::string input); // to create sphere on run-time by clicking V and entering the info with space inbetween
protected:
	void constructScene(std::ifstream& file);
	Color addEffect(const CollisionResult& collision);
	Color addLightEffect(const CollisionResult& collision);
	Color modulateColor(Color& color, const double factor);
	Color darken(Color& color, const int& amount);
	CollisionResult checkIntersect(const Ray& ray);
};

