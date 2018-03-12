#include "Hud.h"

void HUD::draw(sf::RenderWindow* renderer) {
	for (std::list<sf::RectangleShape*>::iterator it=rectangulos.begin(); it != rectangulos.end(); ++it) {
		renderer->draw(**it);
	}
}

HUD::HUD() {
	//HUD
	sf::RectangleShape* hudSeparator= new sf::RectangleShape(sf::Vector2f(800, 5));
	hudSeparator->setFillColor(sf::Color(200, 200, 200, 255));
	hudSeparator->setPosition(0, 100);
	rectangulos.push_back(hudSeparator);

	sf::RectangleShape* objectsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	objectsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	objectsSeparator->setPosition(200, 0);
	rectangulos.push_back(objectsSeparator);

	sf::RectangleShape* actionsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	actionsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	actionsSeparator->setPosition(500, 0);
	rectangulos.push_back(actionsSeparator);



	//HP
	sf::RectangleShape* vidaSeparator =new sf::RectangleShape(sf::Vector2f(100, 50));
	vidaSeparator->setFillColor(sf::Color(0, 0, 0, 255));
	vidaSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	vidaSeparator->setOutlineThickness(5);
	vidaSeparator->setPosition(80, 35);
	rectangulos.push_back(vidaSeparator);


}


HUD::~HUD() {
	rectangulos.clear();
}