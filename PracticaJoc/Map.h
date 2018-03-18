#pragma once
#pragma once
#include <list>
#include "intergerPos.h"
#include <random>
#include <cmath>

class Map {
protected:
	int mapa[21][16];

public:
	Map() {
		//paredes externas
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 16; j++) {
				if (i == 0 || j == 0 || i == 20 || j == 15) {
					mapa[i][j] = 1;
				}
				else {
					mapa[i][j] = 0;
				}
			}
		}
		//paredes habitaciones i cofres
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				//paredes
				mapa[1 + (i * 5) + 4][1 + (j * 5) + 0] = 1;
				mapa[1 + (i * 5) + 4][1 + (j * 5) + 1] = 1;
				mapa[1 + (i * 5) + 4][1 + (j * 5) + 3] = 1;
				mapa[1 + (i * 5) + 4][1 + (j * 5) + 4] = 1;
				mapa[1 + (i * 5) + 4][1 + (j * 5) + 4] = 1;
				mapa[1 + (i * 5) + 3][1 + (j * 5) + 4] = 1;
				mapa[1 + (i * 5) + 2][1 + (j * 5) + 4] = 1;
				mapa[1 + (i * 5) + 0][1 + (j * 5) + 4] = 1;

				//cofres
				int cofreX = rand() * 2 / RAND_MAX;
				int cofreY = rand() * 2 / RAND_MAX;
				mapa[1 + (i * 5) + 1 + cofreX][1 + (j * 5) + 1 + cofreY];

			}
		}
		
	};
	bool canMove(int x, int y) {
		return !(mapa[x][y]);
	}
	intergerPosition getPlayerRoom(intergerPosition cellPos) {
		intergerPosition ret;
		ret.x = cellPos.x / 5;
		ret.y = cellPos.y / 5;
	};

};

class MapClient : Map {
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