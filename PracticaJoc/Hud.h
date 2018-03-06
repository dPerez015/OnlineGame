#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class HUD {
private: 
	std::list<sf::RectangleShape> rectangulos;

public:
	HUD();
	~HUD();
	void draw();
};