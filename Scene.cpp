#pragma once
#include "Scene.h"

Scene::Scene(std::ifstream& file)
	: _pCam(nullptr)
{
	constructScene(file);
}

Scene::~Scene(void)
{
	delete _pCam;
}


enum Command {
	background = 0,
	cam = 1,
	camera = 1,
	sphere = 2,
	fov = 3,
	light = 4,
	plane = 5,
	square = 6,
	comment = 99
};

Command stringToCommand(const std::string& cmd)
{
	if (cmd == "background")
	{
		return background;
	}
	else if (cmd == "camera")
	{
		return camera;
	}
	else if (cmd == "sphere")
	{
		return sphere;
	}
	else if (cmd == "light")
	{
		return light;
	}
	else if (cmd == "plane")
	{
		return plane;
	}
	else if (cmd == "square")
	{
		return square;
	}
	return comment;
}


std::vector<std::string> split(std::string& strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}



void verifyAllSettingsWereFound(bool tblVer[5])
{
	if (tblVer[0] == false) { std::cout << "Warning : the information related to the background was not found in the given file." << std::endl; }
	if (tblVer[1] == false) { std::cout << "Warning : the information related to the camera was not found in the given file." << std::endl; }
	if (tblVer[2] == false) { std::cout << "Warning : no spheres were found in the given file." << std::endl; }
	//if (tblVer[3] == false) { std::cout << "Warning : the information related to the FOV was not found in the given file." << std::endl; }
	if (tblVer[4] == false) { std::cout << "Warning : the information related to the lighting was not found in the given file." << std::endl; }
}




void Scene::constructScene(std::ifstream& file)
{
	std::string line;
	bool tblSettingsVerification[5] = { false, false, false, false, false };
	while (getline(file, line))
	{
		auto strings{ split(line, ' ') };
		const Command command{ stringToCommand(strings[0]) };
		switch (command)
		{
		case background:
			_color = { (octet)stoi(strings[1]) ,(octet)stoi(strings[2]) ,(octet)stoi(strings[3]) };
			tblSettingsVerification[0] = true;
			break;
		case camera:
			delete _pCam;
			_pCam = new Camera({ stof(strings[1]), stof(strings[2]), stof(strings[3]) }, stof(strings[4]), stoi(strings[5]), stoi(strings[6]));
			tblSettingsVerification[1] = true;
			break;
		case sphere:
			addGeometry(line);
			tblSettingsVerification[2] = true;
			break;
		case light:
			_tblGeo.push_back(new Sphere{ {std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3])}, 3,  { (octet)255,(octet)255,(octet)0} });
			_light = new Light{ { stof(strings[1]), stof(strings[2]), stof(strings[3]) } };
			tblSettingsVerification[4] = true;
			break;
		case plane:
			addGeometry(line);
			break;
		case square:
			addGeometry(line);
			break;
		case comment:
			break;
		}
	}
	verifyAllSettingsWereFound(tblSettingsVerification);
}

void Scene::moveAllSphere(const int& frame)
{

	double prog = (frame / 100.0f) * (180 / 3.1415);
	if (_tblGeo.size() > 7)
	{
		_tblGeo[1]->moveTo({ 5 * cos(prog / 20), 5  * sin(prog / 20) , 20 +  20  * sin(prog / 80)});
		_tblGeo[2]->moveTo({ 10 * cos(prog / 10), 10 * sin(prog / 10), 50 + 20 * sin(prog / 80) });
		_tblGeo[3]->moveTo({ 15 * cos(prog / 5),   15 * sin(prog / 5),  30 + 20 * sin(prog / 80) });
		_tblGeo[4]->moveTo({ 20 * cos(prog / 3),   20 * sin(prog / 3),  10 + 20 * sin(prog / 80) });
		_tblGeo[5]->moveTo({ 25 * cos(prog / 7),   25 * sin(prog / 7),  5 + 20 * sin(prog / 80) });
		_tblGeo[6]->moveTo({ 30 * cos(prog / 40),   30 * sin(prog / 40),  25 + 20 * sin(prog / (80)) });
	}
}

void Scene::moveCameraToward(const Vector3d& pos)
{
	_pCam->moveCameraToward(pos);
}

Color Scene::returnColorToUse(const int& x, const int& y)
{

	CollisionResult p = checkIntersect(_pCam->buildRay(x, y));

	if (p.collided)
	{
		return  addEffect(p);
	}
	else
	{
		return _color;
	}
}

Color Scene::darken(Color& color, const int& amount)
{
	const octet oamount{ static_cast<octet>(amount) };
	(color.b - amount < 0) ? color.b = 1 : color.b -= oamount;
	(color.r - amount < 0) ? color.r = 1 : color.r -= oamount;
	(color.g - amount < 0) ? color.g = 1 : color.g -= oamount;
	return color;
}

Color Scene::modulateColor(Color& color, double factor)
{
	const int r{ (int)(color.r * factor) };
	const int g{ (int)(color.g * factor) };
	const int b{ (int)(color.b * factor) };
	return { (octet)std::min(std::max(r, 0), 255), (octet)std::min(std::max(g, 0), 255), (octet)std::min(std::max(b, 0), 255) };
}

Color Scene::addLightEffect(const CollisionResult& collision)
{
	Color returnColor = collision.color;
	if (collision.index != 0)
	{
		const Vector3d Lfull = (_light->getLightPosition() - collision.intersectionPosition);
		const Vector3d L{ Lfull.normalized() };
		if (Ray{ collision.intersectionPosition, L }.checkIfLightBlocked(_tblGeo, collision, Lfull.magnitude()))
		{
			returnColor = modulateColor(returnColor, 0.2f);
		}
		else
		{
			Vector3d N = collision.normal;
			N.normalize();
			returnColor = modulateColor(returnColor, std::max(0.01, L.produitScalaire(N)));
		}
	}
	return returnColor;
}


Color Scene::addEffect(const CollisionResult& collision)
{
	Color resultingColor = collision.color;
	resultingColor = addLightEffect(collision);
	return resultingColor;
}


Vector3i Scene::getDimension()
{
	return _pCam->getDimension();
}

bool Scene::addGeometry(std::string input)//const Vector3d& pos, const Pixel& col, const float& radius)
{
	try {
		_tblGeo.push_back(_geoFactory.BuildGeometry(input));
		return true;
	}
	catch (const std::exception&)
	{
	}
	return false;
}

CollisionResult Scene::checkIntersect(const Ray & ray)
{
	if (_tblGeo.empty())
	{
		return CollisionResult();
	}

	bool firstCollision = true;
	CollisionResult closestCollision;
	for (size_t i = 0; i < _tblGeo.size(); i++)
	{
		CollisionResult tempResult = ray.checkContactWithGeometry(*_tblGeo[i]);
		if (tempResult.collided)
		{
			if ((tempResult.distance < closestCollision.distance) or (firstCollision))
			{
				closestCollision = tempResult;
				closestCollision.index = static_cast<int>(i);
				firstCollision = false;
			}
		}
	}
	return closestCollision;
}