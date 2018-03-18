#pragma once
#include "PlayerInfo.h"
#include <map>
#include <SFML\Network.hpp>
#include "utils.h"
#include "player.h"
#include <iostream>
#include "Hud.h"

extern bool waitingForPlayers;

void manageCommandClient(std::string command, std::map<int, Player*>* players,sf::TcpSocket* socket, HUD* hud) {
	std::vector<std::string> words = commandToWords(command);
	if (words[0] == "chat") {
		//aMensajes.push_back(words[1]);
	}
	else if (words[0] == "vis") {
		//players[words[1]]
	}
	else if (words[0] == "turn") {
		//turn = std::stoi(words[1]);
		std::cout << "Es mi turno\n";
		hud->unblock();
	}

	else if (words[0] == "move") {
		(*players)[std::stoi(words[1])]->move(intergerPosition(std::stoi(words[2]), std::stoi(words[3])));
	}

	else if (words[0] == "chest") {
		//map.chest.setPosition(std::stoi(words[1]), std::stoi(words[2]));
	}

	else if (words[0] == "item") {
		//player.addItem(itemStringToEnum(words[1]));
	}

	else if (words[0] == "hit") {
		//player.removeItem(ItemList(armor));
	}

	else if (words[0] == "dead") {
		/*if (std::stoi(words[1]) == player.getPlayerID()) {
			//you are dead
		}
		*/
		std::string msj = "El jugador " + words[2] + " ha matado al jugador " + words[1];
		//aMensajes.push_back(msj);
	}

	else if (words[0] == "win") {
		std::string msj = "Fin de la partida. El jugador " + words[1] + " ha ganado!!";
		//aMensajes.push_back(msj);
		//fin de la partida. Como se señaliza? con un bool?
	}

	else if (words[0] == "disconnect") {
		std::string msj = "El jugador " + words[1] + " se ha desconectado";
		//aMensajes.push_back(msj);
	}
	else if (words[0] == "error") {
		std::string msj = "La accion que ha seleccionado no se puede ejecutar";
		//aMensajes.push_back(msj);
	}
}