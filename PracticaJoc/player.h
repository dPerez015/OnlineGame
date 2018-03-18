#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <vector>
#include <intergerPos.h>
#include <PlayerInfo.h>

class Player: public PlayerInfo{
private:
	std::vector<sf::RectangleShape*> rectangles;
	sf::Vector2f size;
	sf::Vector2f offSet;
	bool isVisible;
public:
	Player(sf::Vector2f rectSize, sf::Vector2f screenOffset) {
		pos.x = -1;
		pos.y = -1;
		size = rectSize;
		offSet = screenOffset;
		isVisible = false;

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

		items = std::vector<bool>((4, false));
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

	void makeVisible(bool v) {
		isVisible = v;
	}
	bool getVisible() {
		return isVisible;
	}
	void setControlable() {
		rectangles[3]->setOutlineColor(sf::Color(0, 255, 0, 255));
		rectangles[3]->setOutlineThickness(2);
	}

	void draw(sf::RenderWindow* renderer) {
		for (std::vector<sf::RectangleShape*>::iterator it = rectangles.begin(); it != rectangles.end(); ++it) {
			renderer->draw(**it);
		}
	}

};
