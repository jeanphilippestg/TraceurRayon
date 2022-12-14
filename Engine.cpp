#include "Engine.h"

Engine::Engine(Scene* scene) // could put the fullscreen option here
{
	_theScene = scene;
}
Engine::~Engine()
{

}

bool Engine::createFrame(sf::RenderWindow& window)
{
	Vector3i dimension = _theScene->getDimension();
	static sf::Image* image = NULL;
	if (!image)
	{
		image = new sf::Image;
		image->create(dimension.x, dimension.y, sf::Color(0, 0, 0));
	}
	#pragma omp parallel for
	for (int y = 0; y < dimension.y; y++)
	{
		#pragma omp parallel for
		for (int x = 0; x < dimension.x; x++)
		{
			const Color c = (*_theScene).returnColorToUse(x, y);
			image->setPixel(x, y, sf::Color(c.r, c.g, c.b));
		}
	}

	_texture.loadFromImage(*image);
	_frame.setTexture(_texture);

	window.clear(sf::Color::Black);
	window.draw(_frame);
	window.display();

	return true;
}

bool Engine::simulate()
{
	const Vector3i dimension = _theScene->getDimension();
	const bool fullScreen = false;
	sf::RenderWindow window(sf::VideoMode(dimension.x, dimension.y), "", fullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	bool noError = true;
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		inputManager(window);
		noError = createFrame(window);
		_theScene->moveAllSphere(_tick++);
		if (_tick > 3600000) _tick = 0;
	}
	return noError;
}

//wasd, c to go down, z to go up, might add a key to add sphere on runtime (console-like)
void Engine::inputManager(sf::RenderWindow& window)
{
	sf::Event _event;
	while (window.pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (_event.type == sf::Event::KeyPressed)
		{
			const sf::Keyboard::Key cle{ _event.key.code };
			if (cle == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (_console)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					std::cout << "Executing : ";
					if (!_theScene->addGeometry(_input))
					{
						std::cout << "Invalid command: " << _input.toAnsiString() << std::endl;
						_input = "";
					}
				}
			}
		}
		else if (_event.type == sf::Event::TextEntered)
		{
			if (_event.text.unicode == 'v')
			{
				//_console = !_console;
				const char sign{ _console ? '+' : '-' };
				std::cout << "[" << sign << " Mode Console " << sign << "]" << std::endl;
				_input = "";
			}
			else if (_console)
			{
				_input += _event.text.unicode;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_theScene->moveCameraToward({ 0, 0, 1 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_theScene->moveCameraToward({ -1, 0, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_theScene->moveCameraToward({ 0, 0, -1 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_theScene->moveCameraToward({ 1, 0, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		_theScene->moveCameraToward({ 0, -1, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		_theScene->moveCameraToward({ 0, 1, 0 });
	}

}