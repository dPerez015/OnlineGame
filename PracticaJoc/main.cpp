#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "Hud.h"

int main() {
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