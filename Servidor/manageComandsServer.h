#pragma once
#include "PlayerInfo.h"
#include <map>
#include <SFML\Network.hpp>
#include "utils.h"
#include "PlayerInfo.h"
#include <Map.h>

extern Map mapa;

void manageCommandServer(std::string command, std::map<int,PlayerInfo> &players, int id, std::map<int, sf::TcpSocket*> &clients) {
	std::vector<std::string> words = commandToWords(command);
	if (words[0] == "chat") {
		std::string msj = "chat_" + players[id].getNickname() + ": " + words[1];
		for (int i = 0; i < clients.size(); ++i) {
			clients[i]->send(msj.c_str(), msj.length());
		}
	}

	else if (words[0] == "w") {
		//check if valid movement direction
		intergerPosition direction=charToDir(words[2]);
		
		if (mapa.canMove(players[id].getPosition().x+direction.x, players[id].getPosition().y + direction.y)) {
			players[id].setPosition(players[id].getPosition().x + direction.x, players[id].getPosition().y + direction.y);
			intergerPosition playerRoom = mapa.getPlayerRoom(players[id].getPosition());
			for (std::map<int, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end();++it) {
				//(*it).first
				if (playerRoom == mapa.getPlayerRoom(players[(*it).first].getPosition())) {
					std::string msj = "move_";
					msj += id;
					msj += "_";
					msj += players[id].getPosition().x;
					msj += "_";
					msj += players[id].getPosition().y;

					(*it).second->send(msj.c_str(), msj.size());
				}

			}

		}
			//if not valid, resend error msj ---> clients[id] hauria de funcionar
			//clients[id]->send("error", 5);

			//if is valid, change my local information
			//then send to everybody who needs to know
	}

	else if (words[0] == "a") {
		//if position = enemy then 
		//if enemy isnt blocking in oposite dir then 
		//send hit to him

		//else nothing or send to player "missed"
	}

	else if (words[0] == "s") {
		//if position = chest then send item to him

		//else nothing or send to player an error command
	}

	else if (words[0] == "b") {
		if (players[id].hasItem(ItemList(shield))) {
			players[id].blockingDirection = words[1];
		}
		else {
			clients[id]->send("error", 5);
		}
	}

	else if (words[0] == "nick") {
		players[id].setNickname(words[1]);
	}
}