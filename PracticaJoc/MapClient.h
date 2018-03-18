#pragma once
#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "intergerPos.h"
#include <random>
#include <cmath>
#include <Map.h>

class MapClient : public Map {
private:	
	std::list<sf::RectangleShape*> rectangulos;
	sf::Color blockColor;
	sf::Color chestColor;
	sf::Vector2f rectSize;

public:
	sf::Vector2f getRectSize() {
		return rectSize;
	}

	MapClient(sf::Vector2f windowSize):Map() {
		blockColor = sf::Color(150, 150, 150, 255);
		chestColor = sf::Color(153, 102, 0, 255);
		rectSize=sf::Vector2f(windowSize.x/ 21.f, windowSize.y /16.f);

		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 16; j++) {
				if (mapa[i][j]==1) {
					sf::RectangleShape* rect = new sf::RectangleShape(rectSize);
					rect->setPosition((i*rectSize.x) + (800-windowSize.x),(j*rectSize.y)+(600-windowSize.y));
					rect->setFillColor(blockColor);
					rectangulos.push_back(rect);
				}
			}
		}
	}

	void draw(sf::RenderWindow* renderer) {
		for (std::list<sf::RectangleShape*>::iterator it = rectangulos.begin(); it != rectangulos.end(); ++it) {
			renderer->draw(**it);
		}
	}

	void addCofre(intergerPosition pos) {
		sf::RectangleShape* rect = new sf::RectangleShape(rectSize);
		rect->setPosition(pos.x*rectSize.x, pos.y*rectSize.y);
		rect->setFillColor(chestColor);
		rectangulos.push_back(rect);

		mapa[pos.x][pos.y] = 1;
	}
};