#pragma once
#include "PlayerInfo.h"
#include <map>
#include <SFML\Network.hpp>
#include "utils.h"
#include "PlayerInfo.h"
#include <Map.h>

extern Map mapa;

void manageCommandServer(std::string command, std::map<int,PlayerInfo> &players, int id, std::map<int, sf::TcpSocket*> &clients,std::vector<int> &turnOrder, int &turnIndex) {
	std::vector<std::string> words = commandToWords(command);
	if (words[0] == "chat") {
		std::string msj = "chat_" + players[id].getNickname() + ": " + words[1];
		for (int i = 0; i < clients.size(); ++i) {
			clients[i]->send(msj.c_str(), msj.length());
		}
	}

	else if (words[0] == "nick") {
		players[id].setNickname(words[1]);
	}
	else {
		if (turnOrder[turnIndex] == id) {
			turnIndex = (turnIndex+1)%turnOrder.size();
			if (words[0] == "w") {
				//check if valid movement direction
				intergerPosition direction = charToDir(words[1]);

				if (mapa.canMove(players[id].getPosition().x + direction.x, players[id].getPosition().y + direction.y)) {
					players[id].setPosition(players[id].getPosition().x + direction.x, players[id].getPosition().y + direction.y);
					intergerPosition playerRoom = mapa.getPlayerRoom(players[id].getPosition());
					for (std::map<int, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						
						if (playerRoom == mapa.getPlayerRoom(players[(*it).first].getPosition())) {
							std::string msj = "move_";
							msj += std::to_string(id);
							msj += "_";
							msj += std::to_string(players[id].getPosition().x);
							msj += "_";
							msj += std::to_string(players[id].getPosition().y);

							(*it).second->send(msj.c_str(), msj.size());

							msj = "v_" + std::to_string(id) + "_" + "1";
							(*it).second->send(msj.c_str(), msj.size());

							msj= "v_" + std::to_string((*it).first) + "_" + "1";
							clients[id]->send(msj.c_str(), msj.size());

							msj = "move_" + std::to_string((*it).first) + "_" + std::to_string(players[(*it).first].getPosition().x) + "_" + std::to_string(players[(*it).first].getPosition().y);
							clients[id]->send(msj.c_str(), msj.size());
							std::cout << msj << "\n";
						}
						else {
							std::string msj = "v_" + std::to_string(id) + "_" + "0";
							(*it).second->send(msj.c_str(), msj.size());
							msj = "v_" + std::to_string((*it).first) + "_" + "0";
							clients[id]->send(msj.c_str(), msj.size());
						}
					}

				}
				//if not valid, resend error msj ---> clients[id] hauria de funcionar
				//clients[id]->send("error", 5);
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
			clients[turnOrder[turnIndex]]->send("turn", 5);

		}
	}

	

	
}