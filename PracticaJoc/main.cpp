#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <vector>
#include "Hud.h"
#include "PlayerInfo.h"
#include "button.h"
#include "Map.h"
#include "player.h"
#include <queue>
#include "utils.h"
 
#define MAX_MSJ_SIZE 128

std::mutex mu;
int myID;
std::queue<std::string> commands;
bool connected;

std::map<int, Player*> players;

void receiveThread(sf::TcpSocket* socket){
	std::cout << "Thread para el recieve inicializado!\n";
	char buffer[MAX_MSJ_SIZE];
	std::size_t bytesReceived;
	sf::Socket::Status status;
	bool open = true;;
	while (open) {
		status = socket->receive(&buffer, MAX_MSJ_SIZE, bytesReceived);
		if (status == sf::Socket::Status::Disconnected) {
			open = false;
			socket->disconnect();
			mu.lock();
			std::cout << "Conexion con el servidor perdida\n";
			connected = false;
			mu.unlock();
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			mu.lock();
			//std::cout << "Servidor: " << buffer << std::endl;
			commands.push(buffer);
			mu.unlock();
		}
	}
};

int main() {
	
	//PARTE DE CONEXIÓN CON EL SERVIDOR-------------------------------------------------------
	sf::TcpSocket socket;
	sf::Socket::Status status;
	std::thread t1;

	std::cout << "Escribe tu nombre: \n";
	std::string nick;
	std::cin >> nick;
	
	std::cout << "Establecimiento de conexion...\n";
	if (socket.connect("127.0.0.1", 50000, sf::seconds(5.f)) != sf::Socket::Status::Done) {
		std::cout << "Problema al conectarse con el servidor\n";
	}
	else {
		std::cout << "Conectado\n";
		//inicializamos el thread para el recieve
		t1 = std::thread(&receiveThread,&socket);
		connected = true;
	}

	nick = "nick_" + nick;
	
	socket.send(nick.c_str(), nick.length()); //enviamos el nick al servidor

	bool waitingForPlayers = true;

	//----------------------------------------------------------------------------------------
	
	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "MegaGame");

	sf::Font font;
	if (!font.loadFromFile("calibril.ttf")) {
		std::cout << "no se puede leer la font\n" << std::endl;
	}

	HUD hud(&socket);

	MapClient map(sf::Vector2f(600,495));
	
	Player player(map.getRectSize(), sf::Vector2f(200,105));

	Player player2(map.getRectSize(), sf::Vector2f(200, 105));

	Player player3(map.getRectSize(), sf::Vector2f(200, 105));

	Player player4(map.getRectSize(), sf::Vector2f(200, 105));

	players.emplace(0, &player);
	players.emplace(1, &player2);
	players.emplace(2, &player3);
	players.emplace(3, &player4);


	hud.setMap(&map);
	//hud.setPlayer(&myID);
	
	//Button button((std::string)"prueba", sf::Vector2f(300,300), sf::Vector2f(100, 100),font,16);

	while (window.isOpen() && connected)
	{
		if (waitingForPlayers) {
			if (!commands.empty()) {
				std::vector<std::string> words = commandToWords(commands.front());
				if (words[0] == "id") {
					hud.setPlayer(players[std::stoi(words[1])]);
				}
				else if (words[0] == "move") {
					std::cout << words[2]<<"	"<<words[3];
					players[std::stoi(words[1])]->move(intergerPosition(std::stoi(words[2]), std::stoi(words[3])));
				}
				else if (words[0] == "con") {
					std::cout << "Se ha conectado un nuevo jugador\n";
				}
				else if (words[0] == "start") {
					waitingForPlayers = false;
				}
				commands.pop();
			}
			//DRAW HUD
			hud.draw(&window);
			map.draw(&window);
			//player.draw(&window);
			

			//clear
			window.display();
			window.clear();
		}
		else {
			sf::Event evento;
			while (window.pollEvent(evento)) {
				switch (evento.type) {
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
			for (std::map<int, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
				(*it).second->draw(&window);
			}

			//clear
			window.display();
			window.clear();
		}
	}
}