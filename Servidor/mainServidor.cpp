#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "PlayerInfo.h"
#include "Game.h"
#include <Map.h>
#include "manageComandsServer.h"

#define MAX_MSG_SIZE 128

void cleanup();
void receiveThread(sf::TcpSocket* socket,int id);
std::thread t1, t2, t3, t4;
std::map<int,PlayerInfo> players;
std::map<int,sf::TcpSocket*> clients;
std::mutex mu;
Map mapa;
std::vector<int> turnOrder;
int turnIndex = 0;


void inicializarThread(int clientNumber, sf::TcpSocket* socket) {
	if (clientNumber == 0) t1 = std::thread(&receiveThread, socket,clientNumber);
	else if(clientNumber == 1) t2 = std::thread(&receiveThread, socket, clientNumber);
	else if (clientNumber == 2) t3 = std::thread(&receiveThread, socket, clientNumber);
	else if (clientNumber == 3) t4 = std::thread(&receiveThread, socket, clientNumber);
}

void receiveThread(sf::TcpSocket* socket,int id) {
	std::cout << "Thread para el recieve inicializado!\n";
	char buffer[MAX_MSG_SIZE];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;
	while (open) {
		status = socket->receive(buffer, MAX_MSG_SIZE, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			socket->disconnect();
			std::cout << "Conexion con el cliente "<< id << " perdida\n";
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			std::cout << "El cliente " << id << " envia el siguiente mensaje: " << buffer << std::endl;
			//tratar el mensaje
			
			mu.lock();
			manageCommandServer(buffer, players, id, clients,turnOrder,turnIndex);
			
			mu.unlock();
		}
	}
};

int main() {
	
	sf::TcpListener listener;
	
	

	if (listener.listen(50000) != sf::Socket::Done) {
		std::cout << "Problema al escuchar por el puerto 50000\n";
	}
	else {
		std::cout << "Puerto 50000 abierto\n";
	}


	

	//conexión de los 4 clientes. Suponemos que no se desconectan hasta que empieza la partida.
	for (int i = 0; i < 4; i++) {
		sf::TcpSocket* incomingClient = new sf::TcpSocket;
		if (listener.accept(*incomingClient) == sf::Socket::Done) {
			std::cout << "Nuevo cliente aceptado\n";
			clients[i]= incomingClient;
			players[i]=PlayerInfo(i);
			char buffer[MAX_MSG_SIZE];
			size_t bytesRecibed;
			sf::Socket::Status status = incomingClient->receive(buffer,MAX_MSG_SIZE,bytesRecibed);
			if (status!=sf::Socket::Status::Done) {
				std::cout << "Ha habido un problema al inicializar la conexion con este client\n";
				incomingClient->disconnect();
				clients.erase(i);
				players.erase(i);
			}
			else {
				buffer[bytesRecibed] = '\0';
				std::vector<std::string> words = commandToWords(buffer);
				players[i].setNickname( words[1]);

				std::string msj = "id_" + std::to_string(i);
				incomingClient->send(msj.c_str(), msj.length()); //send con la ID que se le assigna
				
				for (std::map<int, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++) {
					(*it).second->send("con",4);
				}
				
				inicializarThread(i, incomingClient); //abrir el thread para ese socket
			}
		}
		turnOrder.push_back(i); //orden de turno
	}
	listener.close();
	//nos aseguramos que todos los clientes han introducido su nick
	bool nicknamesReady = false;
	while (!nicknamesReady) {
		nicknamesReady = true;
		for (int i = 0; i < clients.size(); ++i) {
			if (players[i].getNickname() == "") {
				nicknamesReady = false;
				break;
			}
		}
	}
	std::cout << "Todos los jugadores listos. Empieza el juego!\n";
	//Aqui ya hay 4 clientes conectados y puede empezar el juego

	std::string initialPosMsj="move_0_1_1";
	clients[0]->send(initialPosMsj.c_str(), initialPosMsj.size());
	players[0].setPosition(1, 1);
	
	initialPosMsj = "move_1_1_14";
	clients[1]->send(initialPosMsj.c_str(), initialPosMsj.size());
	players[1].setPosition(1, 15);

	initialPosMsj = "move_2_19_1";
	clients[2]->send(initialPosMsj.c_str(), initialPosMsj.size());
	players[2].setPosition(20, 1);

	initialPosMsj = "move_3_19_14";
	clients[3]->send(initialPosMsj.c_str(), initialPosMsj.size());
	players[3].setPosition(20, 15);


	for (std::map<int, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++) {
		(*it).second->send("start", 6);
	}

	//game loop
	while (players.size()>1) {



	}

	std::cout << "Partida acabada\n";
	(*clients.begin()).second->send("win", 4);

	
	cleanup();
	system("PAUSE");
}

void cleanup() {
	
}