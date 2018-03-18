#pragma once
#include <string>
#include <vector>
#include "intergerPos.h"
enum ItemList { boots, armor, shield, bow };

class PlayerInfo {
protected:
	int playerID; //1,2,3 or 4
	std::string nickname;
	std::vector<bool> items; //objetos
	intergerPosition pos;

	
public:
	PlayerInfo() {};
	PlayerInfo(int id) { playerID = id; };
	void setPlayerID(int id) { playerID = id; };
	int getPlayerID() { return playerID; }
	void setNickname(std::string s) { nickname = s; }
	std::string getNickname() { return nickname; }
	void addItem(ItemList i) { items[i] = true; }
	void removeItem(ItemList i) { items[i] = false; }
	bool hasItem(ItemList i) { return items[i]; }
	void setPosition(int x, int y) { pos.x = x; pos.y = y; }
	intergerPosition getPosition() { return pos; }

	//more variables
	std::string blockingDirection = "";
/*

	static ItemList itemStringToEnum(std::string item) {
		if (item == "boots") return ItemList(boots);
		else if (item == "armor") return ItemList(armor);
		else if (item == "shield") return ItemList(shield);
		else /*if (item == "bow") return ItemList(bow);
	}*/

};
