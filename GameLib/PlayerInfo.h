#pragma once
#include <string>
#include <vector>

enum ItemList { boots, armor, shield, bow };

class ClientProxy {
	int playerID; //1,2,3 or 4
	std::string nickname;
	std::vector<bool> items; //objetos
	std::vector<int> position;

	ClientProxy(int id) {
		playerID = id;
	};

public:
	int getPlayerID() { return playerID; }
	void setNickname(std::string s) { nickname = s; }
	std::string getNickname() { return nickname; }
	void addItem(ItemList i) { items[i] = true; }
	void removeItem(ItemList i) { items[i] = false; }
	void setPosition(int x, int y) { position[0] = x; position[1] = y; }
	std::vector<int> getPosition() { return position; }
};