#include "button.h"

Button::Button(std::string s,sf::Vector2f rectPos ,sf::Vector2f rectSize, sf::Font& f,float textSize, sf::Color main, sf::Color over, sf::Color presed){
	text.setString(s);
	font = f;
	text.setFont(font);
	text.setCharacterSize(textSize);
	text.setPosition(rectPos);
	
	rect.setPosition(rectPos);
	rect.setSize(rectSize);

	mainColor = main;
	overColor = over;
	selectedColor = presed;

	rect.setFillColor(main);

	state = buttonState::unselected;
}

void Button::update(sf::Vector2f mousePosition) {
	//checkMouseOver
	if (rect.getGlobalBounds().contains(mousePosition)) {
		if (state == buttonState::unselected) {
			state = buttonState::over;
			rect.setFillColor(overColor);
			//std::cout << (int)rect.getFillColor().r << "	" << (int)rect.getFillColor().g << "	" << (int)rect.getFillColor().b << "\n";
		}	
	}
	else {
		if (state == buttonState::over) {
			state = buttonState::unselected;
			rect.setFillColor(mainColor);
			//std::cout << (int)rect.getFillColor().r << "	" << (int)rect.getFillColor().g << "	" << (int)rect.getFillColor().b << "\n";
		}

	}
}

bool Button::checkClick(sf::Vector2f mousePosition) {
	if (rect.getGlobalBounds().contains(mousePosition)) {
		
		if (state != buttonState::pressed) {
			state = buttonState::pressed;
			rect.setFillColor(selectedColor);
			return true;
		}
	}
	return false;
}

void Button::unselect() {
	state = buttonState::unselected;
	rect.setFillColor(mainColor);
}

void Button::draw(sf::RenderWindow* renderer) {
	renderer->draw(rect);
	renderer->draw(text);
}