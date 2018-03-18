#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "PlayerInfo.h"
#include "utils.h"

#define MAX_MSG_SIZE 100

std::mutex mu;
std::vector<std::string> commands;
std::thread t1, t2, t3;
void receiveThread(sf::TcpSocket* socket);

void inicializarThreads(std::vector<sf::TcpSocket*> peers) {
	for (int i = 0; i < peers.size(); ++i) {
		if (i == 0) t1 = std::thread(&receiveThread, peers[i]);
		else if (i == 1) t2 = std::thread(&receiveThread, peers[i]);
		else if (i == 2) t3 = std::thread(&receiveThread, peers[i]);
	}
}

//sendAll
void sendToAllPeers(std::vector<sf::TcpSocket*> peers,std::string msj) {
	for (int i = 0; i < peers.size(); ++i) {
		peers[i]->send(msj.c_str(), msj.length());
	}
}

//receiveThread
void receiveThread(sf::TcpSocket* socket) {
	std::cout << "Thread para el recieve inicializado!\n";
	char buffer[MAX_MSG_SIZE];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;
	while (open) {
		status = socket->receive(buffer, MAX_MSG_SIZE, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			std::cout << "Conexion con un peer perdida\n";
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			std::cout << "El peer envia el siguiente mensaje: " << buffer << std::endl;
			//tratar el mensaje
			mu.lock();
			commands.push_back(buffer);
			mu.unlock();
		}
	}
};

struct NodeInfo {
	std::string ip, port;
	NodeInfo(std::string _ip, std::string _port) :ip(_ip), port(_port) {}
};

int main() {

	std::vector<sf::TcpSocket*> peers;
	std::vector<PlayerInfo> players;
	int id;
	int myPort;
	
	//PRIMERO CONEXION CON EL BSS
	sf::TcpSocket socket;
	if (socket.connect("127.0.0.1", 50000, sf::seconds(5.f)) != sf::Socket::Status::Done) {
		std::cout << "Problema al conectarse con el servidor\n";
	}
	else {
		std::cout << "Conectado con el BS server\n";
		myPort = socket.getLocalPort();
		//RECIBIR EL NUMERO DE CONEXIONES CON SUS DATOS
		char buffer[MAX_MSG_SIZE];
		std::size_t bytesReceived;		
		if (socket.receive(buffer, MAX_MSG_SIZE, bytesReceived) == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			std::vector<std::string> subStrings = commandToWords(buffer);
			int peerNumberWaiting = std::stoi(subStrings[0]); //obtenemos cuantos peers estan haciendo listen
			id = peerNumberWaiting;
			for (int i = 0; i < peerNumberWaiting; ++i) { //obtenemos los datos de esos peers y nos conectamos a ellos
				sf::TcpSocket* peerConnection = new sf::TcpSocket; 
				if (peerConnection->connect(subStrings[1 + i * 2], std::stoi(subStrings[2 + i * 2]), sf::seconds(5.f)) == sf::Socket::Status::Done) {
					std::cout << "Conectado con " << i + 1 << " peer/s\n";
					peers.push_back(peerConnection);
				}
			}
			//nos desconectamos del servidor
			socket.disconnect();
			//faltan 3-peerNumberWaiting peers por conectarse
			if (peerNumberWaiting < 3) { 
				//hacemos listen con nuestro puerto libre
				sf::TcpListener listener;
				if (listener.listen(myPort) == sf::Socket::Status::Done) {
					std::cout << "Puerto " << myPort << " abierto\n";
					//esperamos a que se conecten todos los peers
					for (int i = 0; i < 3 - peerNumberWaiting; ++i) {
						sf::TcpSocket* peerConnection = new sf::TcpSocket;
						if (listener.accept(*peerConnection) == sf::Socket::Status::Done) {
							std::cout << "Conectado con otro peer. Solo quedan " << 3 - peerNumberWaiting - (i + 1) << std::endl;
							peers.push_back(peerConnection);
						}
					}
					//ya estan todos los peers conectados, podemos cerrar el listener
					listener.close();
				}
			}
		}
	}
	//todos los peers conectados
	std::cout << "Todos los peers conectados!\n";
	inicializarThreads(peers);


	//cin para el nickname y sendAll nickname?

	//game loop
		//tratar commandos[]

	system("PAUSE");
}