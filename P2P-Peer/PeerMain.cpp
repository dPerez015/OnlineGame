#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "PlayerInfo.h"
#include "utils.h"
#include "Game.h"
#include <queue>

#define MAX_MSG_SIZE 100

std::mutex mu;
std::queue<std::string> commands;
std::thread t1, t2, t3;
void receiveThread(sf::TcpSocket* socket);
std::vector<std::string> aMensajes;


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
			socket->disconnect();
			mu.lock();
			std::cout << "Conexion con un peer perdida\n";
			mu.unlock();
			
		}
		else if (status == sf::Socket::Status::Done) {
			buffer[bytesReceived] = '\0';
			//std::cout << "El peer envia el siguiente mensaje: " << buffer << std::endl;
			//tratar el mensaje
			mu.lock();
			commands.push(buffer);
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

	while (window.isOpen())
	{
		mu.lock();
		while (!commands.empty()) {
			manageCommandPeer(commands.front(), players, &aMensajes);
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
					sendToAllPeers(peers, msj);
					mu.lock();
					aMensajes.push_back(mensaje);
					mu.unlock();

					if (aMensajes.size() > 19)
					{
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
					}
					mensaje = ">";
				}
				break;
			case sf::Event::MouseMoved:
				//hud.update(sf::Vector2f(evento.mouseMove.x, evento.mouseMove.y));
				break;
			case sf::Event::MouseButtonPressed:
				//hud.checkClick(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));
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
		/*hud.draw(&window);
		map.draw(&window);
		for (std::map<int, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
			(*it).second->draw(&window);
		}*/
		window.draw(separator);
		mu.lock();
		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, (20 * i) + 120));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}
		mu.unlock();
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);

		//clear
		window.display();
		window.clear();
	}
	

	system("PAUSE");
}