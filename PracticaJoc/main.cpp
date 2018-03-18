#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include "Hud.h"
#include "PlayerInfo.h"
#include "button.h"
#include "Map.h"
 


std::mutex mu;
int playersConnected;
PlayerInfo myInfo;

void receiveThread(sf::TcpSocket* socket) {
	std::cout << "Thread para el recieve inicializado!\n";
	char buffer[100];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;;
	while (open) {
		status = socket->receive(&buffer, 100, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			std::cout << "Conexion con el servidor perdida\n";
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			std::cout << "Servidor: " << buffer << std::endl;
			
			//std::string msj = buffer;
			//std::vector<std::string> subMsj;
			//int wordCount = 0;
			////convertir el mensaje completo a palabras
			//for (int i = 0; i < msj.length(); ++i) {
			//	if (msj[i] != '_') {
			//		subMsj[wordCount] += msj[i];
			//	}
			//	else {
			//		wordCount++;
			//	}
			//}
			////funcion de tratar el comando
			//if (subMsj[0] == "id") {
			//	myInfo.setPlayerID(std::stoi(subMsj[1]));
			//}
		}
	}
};

int main() {
	/*
	//PARTE DE CONEXIÓN CON EL SERVIDOR-------------------------------------------------------
	std::cout << "Establecimiento de conexion...\n";
	sf::TcpSocket socket;
	sf::Socket::Status status;
	std::thread t1;
	
	if (socket.connect("127.0.0.1", 50000, sf::seconds(5.f)) != sf::Socket::Status::Done) {
		std::cout << "Problema al conectarse con el servidor\n";
	}
	else {
		std::cout << "Conectado\n";
		//inicializamos el thread para el recieve
		t1 = std::thread(&receiveThread,&socket);
	}

	
	std::cout << "Escribe tu nombre: \n";
	std::string nick;
	std::cin >> nick;
	
	myInfo.setNickname(nick);
	socket.send(nick.c_str(), nick.length()); //enviamos el nick al servidor

	if (playersConnected < 4) {
		std::cout << "Esperando a los demas jugadores\n";
	}

	while (playersConnected < 4) {

	}
	std::cout << "Empieza el juego!\n";
	
	//----------------------------------------------------------------------------------------
	*/
	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "MegaGame");

	sf::Font font;
	if (!font.loadFromFile("calibril.ttf")) {
		std::cout << "no se puede leer la font\n" << std::endl;
	}

	HUD hud;

	MapClient map(sf::Vector2f(600,495));
	//map
	
	//Button button((std::string)"prueba", sf::Vector2f(300,300), sf::Vector2f(100, 100),font,16);

	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento)) {
			switch (evento.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::MouseMoved:
				hud.update(sf::Vector2f(evento.mouseMove.x, evento.mouseMove.y));
				break;
			case sf::Event::MouseButtonPressed:
				hud.checkClick(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));
				break;
			case sf::Event::TextEntered:
				break;
			default:
				break;
			}
		}

		//DRAW HUD
		hud.draw(&window);
		map.draw(&window);

		//clear
		window.display();
		window.clear();
	}
}