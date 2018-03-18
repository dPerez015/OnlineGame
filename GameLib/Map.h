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