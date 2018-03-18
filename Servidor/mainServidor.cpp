#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "PlayerInfo.h"
#include "Game.h"

#define MAX_MSG_SIZE 100

void cleanup();
void receiveThread(sf::TcpSocket* socket);
std::map<sf::TcpSocket*, int> socketToID; //map para guardar ID segun el socket
std::thread t1, t2, t3, t4;
std::vector<PlayerInfo> players;
std::vector<sf::TcpSocket*> clients;
std::mutex mu;

void inicializarThread(int clientNumber, sf::TcpSocket* socket) {
	if (clientNumber == 1) t1 = std::thread(&receiveThread, socket);
	else if(clientNumber == 2) t2 = std::thread(&receiveThread, socket);
	else if (clientNumber == 3) t3 = std::thread(&receiveThread, socket);
	else if (clientNumber == 4) t4 = std::thread(&receiveThread, socket);
}

void receiveThread(sf::TcpSocket* socket) {
	std::cout << "Thread para el recieve inicializado!\n";
	int id = socketToID[socket];
	char buffer[MAX_MSG_SIZE];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;
	while (open) {
		status = socket->receive(buffer, MAX_MSG_SIZE, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			std::cout << "Conexion con el cliente "<< id << " perdida\n";
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			std::cout << "El cliente " << id << " envia el siguiente mensaje: " << buffer << std::endl;
			//tratar el mensaje
			mu.lock();
			manageCommandServer(buffer, players, id, clients);
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
			clients.push_back(incomingClient);
			int clientNumber = clients.size();
			socketToID[incomingClient] = clientNumber;
			players.push_back(PlayerInfo(clientNumber));
			std::string msj = "id_"+std::to_string(clientNumber);
			incomingClient->send(msj.c_str(), msj.length()); //send con la ID que se le assigna
			inicializarThread(clientNumber, incomingClient); //abrir el thread para ese socket

		}
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
	
	while (true) {

	}

	cleanup();

	system("PAUSE");
}

void cleanup() {
	
}