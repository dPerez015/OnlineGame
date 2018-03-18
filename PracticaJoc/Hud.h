#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "button.h"

class HUD {
private: 
	std::list<sf::RectangleShape*> rectangulos;
	std::list<sf::Text*> texts;
	sf::Font font;
	std::vector<Button*> buttons;
	std::vector<Button*> directionButtons;
	Button* endButton;
	std::string generateButtonsString();

public:
	HUD();
	~HUD();
	void draw(sf::RenderWindow* renderer);
	void update(sf::Vector2f mousePosition);
	void checkClick(sf::Vector2f mousePosition);
};