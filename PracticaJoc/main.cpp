#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include "Hud.h"


void receiveThread(sf::TcpSocket socket) {
	std::cout << "Thread para el recieve inicializado!\n";
	char buffer[100];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;;
	while (open) {
		status = socket.receive(&buffer, 100, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			std::cout << "Conexión con el servidor perdida\n";
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			//tratar el mensaje
			//funcion de tratar el comando?
		}
	}
};

int main() {
	//PARTE DE CONEXIÓN CON EL SERVIDOR-------------------------------------------------------
	std::cout << "Establecimiento de conexión...\n";
	sf::TcpSocket socket;
	sf::Socket::Status status;
	std::thread t1;
	if (socket.connect("127.0.0.1", 50000, sf::seconds(5.f)) != sf::Socket::Status::Done) {
		std::cout << "Problema al conectarse con el servidor\n";
	}
	else {
		std::cout << "Conectado\n";
		//inicializamos el thread para el recieve
		t1 = std::thread(&receiveThread);// , arguments1, argument2);
	}

	//----------------------------------------------------------------------------------------

	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "MegaGame");

	sf::Font font;
	if (!font.loadFromFile("calibril.ttf")) {
		std::cout << "no se puede leer la font\n" << std::endl;
	}

	HUD hud;

	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento)) {
			switch (evento.type){
			case sf::Event::Closed:
				window.close();
				break;
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::TextEntered:
				break;
			default:
				break;
			}
		}

		//DRAW HUD
		hud.draw(&window);

		//clear
		window.display();
		window.clear();
	}
}