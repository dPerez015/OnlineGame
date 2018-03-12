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
	actionsSeparator->setPosition(350, 0);
	rectangulos.push_back(actionsSeparator);
	
	sf::RectangleShape* buttonsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	buttonsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	buttonsSeparator->setPosition(650, 0);
	rectangulos.push_back(buttonsSeparator);

	sf::RectangleShape* subActionsSeparator = new sf::RectangleShape(sf::Vector2f(300,5));
	subActionsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255)); 
	subActionsSeparator->setPosition(350, 40);
	rectangulos.push_back(subActionsSeparator);

	sf::RectangleShape* subActionsSeparator1 = new sf::RectangleShape(sf::Vector2f(5, 60));
	subActionsSeparator1->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator1->setPosition(425, 40);
	rectangulos.push_back(subActionsSeparator1);

	sf::RectangleShape* subActionsSeparator2 = new sf::RectangleShape(sf::Vector2f(5, 60));
	subActionsSeparator2->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator2->setPosition(500, 40);
	rectangulos.push_back(subActionsSeparator2);

	sf::RectangleShape* subActionsSeparator3 = new sf::RectangleShape(sf::Vector2f(5, 60));
	subActionsSeparator3->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator3->setPosition(575, 40);
	rectangulos.push_back(subActionsSeparator3);


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