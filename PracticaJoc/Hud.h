#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "button.h"
#include "player.h"
#include "MapClient.h"

class HUD {
private: 
	std::list<sf::RectangleShape*> rectangulos;
	std::list<sf::Text*> texts;
	sf::Font font;
	std::vector<Button*> buttons;
	std::vector<Button*> directionButtons;
	Button* endButton;
	std::string generateButtonsString();
	Player* ourPlayer;
	MapClient* ourMap;
	sf::TcpSocket* socket;

	bool canPlay;

public:
	HUD(sf::TcpSocket* sock);
	~HUD();
	void draw(sf::RenderWindow* renderer);
	void update(sf::Vector2f mousePosition);
	void checkClick(sf::Vector2f mousePosition);
	void setPlayer(Player* p);
	void setMap(MapClient* m);
	void unblock();
};