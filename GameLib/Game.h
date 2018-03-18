#pragma once
#include "PlayerInfo.h"
#include <map>
#include <SFML\Network.hpp>
#include "utils.h"
#include "PlayerInfo.h"



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
		//player.addItem(itemStringToEnum(words[1]));
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

void manageCommandPeer(std::string command, std::vector<PlayerInfo> players) {
	//alomejor se puede añadir al final el socket/peer/id del que procede (en el receive por ejemplo)
	//se accederia a el con words[words.size()-1]
	std::vector<std::string> words = commandToWords(command);
	int id = std::stoi(words[words.size() - 1]);

	if (words[0] == "chat") {
		//std::string msj = nick + words[1];
		//aMensajes.push_back(msj); //quien se guarda el nick?
	}
	else if (words[0] == "w") {
		//if is a valid move?? nose si caldria comprovarho
		//words[1] es x o direccion??
		players[id].setPosition(std::stoi(words[1]), std::stoi(words[2]));
	}

	else if (words[0] == "a") {
		//cal fer l'atac?
	}

	else if (words[0] == "s") {
		//cal fer el search? si els cofres queden oberts si
		//map.position(words[2],words[2]).openChest();
	}
	
	else if (words[0] == "b") {
		players[id].blockingDirection = words[1]; //como gestionamos esto?
		//players[id].blocking = true;
	}

	else if (words[0] == "nick") {
		players[id].setNickname(words[1]);
	}

	else if (words[0] == "id") {
		//players[id] //redundante?? como se pasa la id? lo gestiona individualmente cada peer?
	}
}