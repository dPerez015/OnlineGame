#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <vector>

struct NodeInfo {
	std::string ip, port;
	NodeInfo(std::string _ip, std::string _port) :ip(_ip), port(_port) {}
};

int main() {

	sf::TcpListener listener;
	
	std::vector<NodeInfo> nodesInfo; //creamos una lista para guardar el ip:port de cada peer

	if (listener.listen(50000) == sf::Socket::Status::Done) {
		std::cout << "Escuchando por el puero 50000.\n";
		for (int i = 0; i < 4; ++i) {
			sf::TcpSocket socket;
			std::cout << "Esperando a que se conecte otro peer\n";
			if (listener.accept(socket) == sf::Socket::Status::Done) {
				std::cout << "Conexion con un peer establecida.\n";
				//ENVIAR EL NUMERO DE CONEXIONES EXTRAS CON SUS DATOS IP+PORT
				int numeroConexiones = nodesInfo.size();
				std::string peersAndInfo = std::to_string(numeroConexiones); //numero de conexiones extras
				for (int j = 0; j < numeroConexiones; ++j) { //copiamos la info de esas conexiones
					peersAndInfo = peersAndInfo + "_" + nodesInfo[j].ip + "_" + nodesInfo[j].port;
				}
				socket.send(peersAndInfo.c_str(), peersAndInfo.length());
				nodesInfo.push_back(NodeInfo(socket.getRemoteAddress().toString(), std::to_string(socket.getRemotePort())));
				socket.disconnect();
			}
		}

		std::cout << "Se han conectado 4 peers y se ha enviado la info para que se conecten entre ellos\n";

		listener.close();

		std::cout << "Listener cerrado\n";
	}
	else {
		std::cout << "Problema en el listen\n";
	}

	system("PAUSE");
}
