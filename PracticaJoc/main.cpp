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
#include "manageCommandClient.h"
 
#define MAX_MSJ_SIZE 128

std::mutex mu;
int myID;
std::queue<std::string> commands;
bool connected;

std::map<int, Player*> players;

std::vector<std::string> aMensajes;

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
	
	//PARTE DE CONEXI�N CON EL SERVIDOR-------------------------------------------------------
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
		std::cout << "No se puede leer la font\n" << std::endl;
	}
	sf::String mensaje = ">";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(200, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);

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
					players[std::stoi(words[1])]->makeVisible(true);
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
				else if (words[0] == "turn") {
					//turn = std::stoi(words[1]);
					std::cout << "Es mi turno\n";
					hud.unblock();
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
			mu.lock();
			while(!commands.empty()) {
				manageCommandClient(commands.front(), &players, &socket, &hud, &aMensajes);
				commands.pop();
			}
			mu.unlock();

			sf::Event evento;
			while (window.pollEvent(evento)) {
				switch (evento.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (evento.key.code == sf::Keyboard::Return) {
						mensaje[0] = ' ';
						std::string msj = "chat_" + mensaje;
						socket.send(msj.c_str(), msj.length());
						mensaje = ">";
					}
					break;
				case sf::Event::MouseMoved:
					hud.update(sf::Vector2f(evento.mouseMove.x, evento.mouseMove.y));
					break;
				case sf::Event::MouseButtonPressed:
					hud.checkClick(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));
					break;
				case sf::Event::TextEntered:
					if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
						mensaje += (char)evento.text.unicode;
					else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
						mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
					break;
				default:
					break;
				}
			}

			//DRAW HUD
			hud.draw(&window);
			map.draw(&window);
			for (std::map<int, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
				if((*it).second->getVisible())
					(*it).second->draw(&window);
			}
			window.draw(separator);
			for (size_t i = 0; i < aMensajes.size(); i++)
			{
				std::string chatting = aMensajes[i];
				chattingText.setPosition(sf::Vector2f(0, (20 * i) + 120));
				chattingText.setString(chatting);
				window.draw(chattingText);
			}
			std::string mensaje_ = mensaje + "_";
			text.setString(mensaje_);
			window.draw(text);

			//clear
			window.display();
			window.clear();
		}
	}
}