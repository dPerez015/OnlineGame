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
public:
	Player(sf::Vector2f rectSize) {
		sf::RectangleShape* cabeza = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4)); 
		cabeza->setFillColor(sf::Color(242,203,167,255));
		rectangles.push_back(cabeza);

		sf::RectangleShape* torax = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		cabeza->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(torax);

		sf::RectangleShape* piernas=new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		cabeza->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(piernas);

		sf::RectangleShape* pies = new sf::RectangleShape(sf::Vector2f(rectSize.x, rectSize.y / 4));
		cabeza->setFillColor(sf::Color(242, 203, 167, 255));
		rectangles.push_back(pies);

	}
	void updatePos() {
		std::vector<sf::RectangleShape*>::iterator it = rectangles.begin();
		int i = 0;
		while (it != rectangles.end()) {
			rectangles[0]->setPosition(pos.x*size.x, (pos.y*size.y)+(size.y*i /4));
			i++;
		}
	}

	void move(intergerPosition newPos) {
		pos = newPos;
		updatePos();
	}

	void getUpgrade(int upgrade) {
		
	}

	void draw(sf::RenderWindow* renderer) {
		for (std::vector<sf::RectangleShape*>::iterator it = rectangles.begin(); it != rectangles.end(); ++it) {
			renderer->draw(**it);
		}
	}

};
