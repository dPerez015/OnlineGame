#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class button {
public: enum buttonState { pressed, over, unselected };
private:
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;

	sf::Color mainColor;
	sf::Color overColor;
	sf::Color selectedColor;

	float textSize;

	buttonState state;
public: 
	button(std::string s, sf::Vector2f rectSize, sf::Font& f, float textSize = 14, sf::Color mainColor = sf::Color(200, 200, 200, 255), sf::Color overColor = sf::Color(200, 200, 0, 255), sf::Color presedColor = sf::Color(0, 200, 0, 255));
	~button();
	void update(sf::Vector2f mousePosition);
	void draw(sf::RenderWindow* renderer);

	void checkClick(sf::Vector2f mousePosition);
	void unselect();
};
