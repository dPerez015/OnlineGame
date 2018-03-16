#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>

//---------variables globales del juego-------------
class gameInfo {
	//tiempo de turno
	//lista jugadores en partida (con su ID y nickname)
	//MAZE_INFO -todo lo relacionado con el mapa (posicion de los cofres, estado de las puertas)
			//el servidor lo tendrá actualizado en todo momento
			//pero el cliente solo se actualizara su habitacion
};


//check if action is valid functions



int main() {
	
	sf::TcpListener listener;
	std::vector<sf::TcpSocket*> clients;
	sf::Socket::Status status;

	if (listener.listen(50000) != sf::Socket::Done) {
		std::cout << "Problema al escuchar por el puerto 50000\n";
	}

	
	for (int i = 0; i < 4; i++) {
		sf::TcpSocket* incomingClient = new sf::TcpSocket;
		if (listener.accept(*incomingClient) == sf::Socket::Done) {
			std::cout << "Nuevo cliente aceptado\n";
			clients.push_back(incomingClient);

			//send con el numero de clientes (y el numero de jugador que es este cliente (esto es el ID?)).
			//recieve con ID + nickname (la ID es para confirmar que es el mismo. El ID es por defecto en cada mensaje?)

		}
		delete incomingClient;
	}
	listener.close();
	//Aqui ya hay 4 clientes conectados y puede empezar el juego
	
	while (true) {

	}


	//system("PAUSE");
}