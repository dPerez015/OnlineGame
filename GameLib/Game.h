#pragma once
#include "PlayerInfo.h"
#include <map>
#include <SFML\Network.hpp>
#include "utils.h"
#include "PlayerInfo.h"



//MAZE_INFO -todo lo relacionado con el mapa (posicion de los cofres, estado de las puertas)
//el servidor lo tendrá actualizado en todo momento
//pero el cliente solo se actualizara su habitacion

//commands
void manageCommandServer(std::string command, std::vector<PlayerInfo> &players, int id, std::vector<sf::TcpSocket*> &clients) {
	std::vector<std::string> words = commandToWords(command);
	if (words[0] == "chat") {
		std::string msj = "chat_"+players[id].getNickname() + ": " + words[1];
		for (int i = 0; i < clients.size(); ++i) {
			clients[i]->send(msj.c_str(), msj.length());
		}
	}

	else if (words[0] == "w") {
		//check if valid movement direction

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


void manageCommandClient(std::string command, PlayerInfo player/*,socket?*/) {
	std::vector<std::string> words = commandToWords(command);
	if (words[0] == "chat") {
		//aMensajes.push_back(words[1]);
	}
	
	else if (words[0] == "turn") {
		//turn = std::stoi(words[1]);
	}

	else if (words[0] == "player") {
		if (std::stoi(words[1]) == player.getPlayerID()) { //its me
			player.setPosition(std::stoi(words[2]), std::stoi(words[3]));
		}
		else {
			//si es otro como lo pinta? actualiza la posicion de otro player en local? pinta directamente la posicion?
		}
	}

	else if (words[0] == "chest") {
		//map.chest.setPosition(std::stoi(words[1]), std::stoi(words[2]));
	}

	else if (words[0] == "item") {
		player.addItem(itemStringToEnum(words[1]));
	}

	else if (words[0] == "hit") {
		player.removeItem(ItemList(armor));
	}

	else if (words[0] == "dead") {
		if (std::stoi(words[1]) == player.getPlayerID()) {
			//you are dead
		}

		std::string msj = "El jugador " + words[2] + " ha matado al jugador " + words[1];
		//aMensajes.push_back(msj);
	}

	else if (words[0] == "win") {
		std::string msj = "Fin de la partida. El jugador "+words[1]+" ha ganado!!";
		//aMensajes.push_back(msj);
		//fin de la partida. Como se señaliza? con un bool?
	}

	else if (words[0] == "disconnect") {
		std::string msj = "El jugador " + words[1] + " se ha desconectado";
		//aMensajes.push_back(msj);
	}

	/*else if (words[0] == "info") {

	}*/

	else if (words[0] == "error") {
		std::string msj = "La accion que ha seleccionado no se puede ejecutar";
		//aMensajes.push_back(msj);
	}

	else if (words[0] == "id") {
		player.setPlayerID(std::stoi(words[1]));
	}
}

