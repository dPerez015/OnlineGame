#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>

int main() {
	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "MegaGame");

	sf::Font font;
	if (!font.loadFromFile("calibril.ttf")) {
		std::cout << "no se puede leer la font\n" << std::endl;
	}

	//HUD
	sf::RectangleShape hudSeparator(sf::Vector2f(800, 5));
	hudSeparator.setFillColor(sf::Color(200, 200, 200, 255));
	hudSeparator.setPosition(0, 100);

	//HP
	sf::RectangleShape vidaSeparator(sf::Vector2f(100,50));
	vidaSeparator.setFillColor(sf::Color(255, 0, 0, 0));
	vidaSeparator.setOutlineColor(sf::Color(200, 200, 200, 255));
	vidaSeparator.setOutlineThickness(5);
	vidaSeparator.setPosition(20, 20);

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
		window.draw(hudSeparator);
		window.draw(vidaSeparator);

		//clear
		window.display();
		window.clear();
	}
}