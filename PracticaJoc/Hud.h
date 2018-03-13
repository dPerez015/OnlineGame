#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>

class HUD {
private: 
	std::list<sf::RectangleShape*> rectangulos;
	std::list<sf::Text*> texts;
	sf::Font font;
public:
	HUD();
	~HUD();
	void draw(sf::RenderWindow* renderer);
};