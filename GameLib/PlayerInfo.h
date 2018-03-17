#pragma once
#include <string>
#include <vector>

enum ItemList { boots, armor, shield, bow };

class PlayerInfo {
	int playerID; //1,2,3 or 4
	std::string nickname;
	std::vector<bool> items; //objetos
	std::vector<int> position;

	
public:
	PlayerInfo() {};
	PlayerInfo(int id) { playerID = id; };
	void setPlayerID(int id) { playerID = id; };
	int getPlayerID() { return playerID; }
	void setNickname(std::string s) { nickname = s; }
	std::string getNickname() { return nickname; }
	void addItem(ItemList i) { items[i] = true; }
	void removeItem(ItemList i) { items[i] = false; }
	void setPosition(int x, int y) { position[0] = x; position[1] = y; }
	std::vector<int> getPosition() { return position; }
};