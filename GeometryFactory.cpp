#pragma once
#include "GeometryFactory.h"


GeometryFactory::GeometryFactory()
{

}
GeometryFactory::~GeometryFactory()
{

}

std::vector<std::string> splitCommand(std::string& strToSplit)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (getline(ss, item, ' '))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}


void GeometryFactory::destroy(Geometry* pGeo)
{
	delete(pGeo);
}


Geometry* GeometryFactory::BuildGeometry(std::string & command)
{
	try {
		auto s= splitCommand(command) ;
		if (s.size() > 7)
		{
			if (s[0] == "sphere")
			{
				return new Sphere{ {std::stof(s[1]), std::stof(s[2]), std::stof(s[3])}, std::stof(s[4]),  { (octet)std::stoi(s[5]),(octet)std::stoi(s[6]),(octet)std::stoi(s[7])} };
			}
			else if (s[0] == "plane")
			{
				return new Plane{ {std::stof(s[1]), std::stof(s[2]), std::stof(s[3])}, { (octet)std::stoi(s[4]),(octet)std::stoi(s[5]),(octet)std::stoi(s[6])}, {std::stof(s[7]), std::stof(s[8]), std::stof(s[9])} };
			}
			else if (s[0] == "square")
			{
				return new Square{ {std::stof(s[1]), std::stof(s[2]), std::stof(s[3])}, {std::stof(s[4]), std::stof(s[5]), std::stof(s[6])}, {std::stof(s[7]), std::stof(s[8]), std::stof(s[9])}, {std::stof(s[10]), std::stof(s[11]), std::stof(s[12])}, {(octet)std::stoi(s[13]), (octet)std::stoi(s[14]), (octet)std::stoi(s[15])} };
			}
		}
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	return nullptr;
}