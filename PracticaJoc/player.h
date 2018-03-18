#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <vector>
#include "intergerPos.h"

class Player {
private:
	intergerPosition pos;
	std::vector<sf::RectangleShape*> rectangles;
	sf::Vector2f size;
	sf::Vector2f offSet;
public:
	Player(sf::Vector2f rectSize, sf::Vector2f screenOffset) {
		pos.x = -1;
		pos.y = -1;
		size = rectSize;
		offSet = screenOffset;

		sf::RectangleShape* cabeza = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4)); 
		cabeza->setFillColor(sf::Color(242,203,167,255));
		rectangles.push_back(cabeza);

		sf::RectangleShape* torax = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		torax->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(torax);

		sf::RectangleShape* piernas=new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		piernas->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(piernas);

		sf::RectangleShape* pies = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		pies->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(pies);

	}
	void updatePos() {
		std::vector<sf::RectangleShape*>::iterator it = rectangles.begin();
		int i = 0;
		while (it != rectangles.end()) {
			(**it).setPosition(pos.x*size.x + offSet.x, (pos.y*size.y)+(size.y*i /4) + offSet.y);
			it++;
			i++;
		}
	}

	void move(intergerPosition newPos) {
		pos = newPos;
		updatePos();
	}
	/*intergerPosition getPos() {
		return pos;
	}*/

	void getUpgrade(int upgrade) {
		
	}

	void draw(sf::RenderWindow* renderer) {
		for (std::vector<sf::RectangleShape*>::iterator it = rectangles.begin(); it != rectangles.end(); ++it) {
			renderer->draw(**it);
		}
	}

};
