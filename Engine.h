#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Main.hpp>
#include "Scene.h"
class Engine
{
private: 
	int _tick = 0;
	Scene* _theScene;
	bool _console = false;
	sf::String _input = "";
	sf::Sprite _frame;
	sf::Texture _texture;
protected: 
	bool createFrame(sf::RenderWindow& window);
	void inputManager(sf::RenderWindow& window);
public:
	Engine(Scene *scene);
	~Engine();
	bool simulate();
};

