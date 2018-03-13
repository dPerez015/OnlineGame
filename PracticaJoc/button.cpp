#include "button.h"

button::button(std::string s, sf::Vector2f rectSize, sf::Font& f,float textSize = 14, sf::Color main = sf::Color(0, 0, 200, 255), sf::Color over = sf::Color(200, 200, 0, 255), sf::Color presed = sf::Color(0, 200, 0, 255)){
	text.setString(s);
	font = f;
	text.setFont(font);
	text.setCharacterSize(textSize);

	mainColor = main;
	overColor = over;
	selectedColor = presed;
}

void button::update(sf::Vector2f mousePosition) {
	//checkMouseOver
	if (rect.getGlobalBounds().contains(mousePosition)) {
		if (state = buttonState::unselected) {
			state = buttonState::over;
			rect.setFillColor(overColor);
		}
		else {
			if (state = buttonState::over) {
				state = buttonState::unselected;
				rect.setFillColor(mainColor);
			}
		}
	}
}

void button::checkClick(sf::Vector2f mousePosition) {
	if (rect.getGlobalBounds().contains(mousePosition)) {
		if (state != buttonState::pressed) {
			state = buttonState::pressed;
			rect.setFillColor(selectedColor);
		}
	}
}

void button::unselect() {
	state = buttonState::unselected;
	rect.setFillColor(mainColor);
}

void button::draw(sf::RenderWindow* renderer) {
	renderer->draw(rect);
	renderer->draw(text);
}