#include "Hud.h"

void HUD::draw(sf::RenderWindow* renderer) {
	for (std::list<sf::RectangleShape*>::iterator it=rectangulos.begin(); it != rectangulos.end(); ++it) {
		renderer->draw(**it);
	}
	for (std::list<sf::Text*>::iterator it = texts.begin(); it != texts.end(); ++it) {
		renderer->draw(**it);
	}
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); ++i) {
		(**i).draw(renderer);
	}
	for (std::vector<Button*>::iterator i = directionButtons.begin(); i != directionButtons.end(); ++i) {
		(**i).draw(renderer);
	}
	endButton->draw(renderer);
}

void HUD::update(sf::Vector2f mousePosition) {
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); ++i) {
		(**i).update(mousePosition);
	}
	for (std::vector<Button*>::iterator i = directionButtons.begin(); i != directionButtons.end(); ++i) {
		(**i).update(mousePosition);
	}
	endButton->update(mousePosition);
}

void HUD::setPlayer(Player* p) {
	ourPlayer = p;
}

void HUD::setMap(MapClient* m) {
	ourMap = m;
}

void HUD::checkClick(sf::Vector2f mousePosition) {
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); ++i) {
		//(**i).unselect();
		if ((**i).checkClick(mousePosition)) {
			for (std::vector<Button*>::iterator j = buttons.begin(); j != buttons.end(); ++j) {
				if(j!=i)
					(**j).unselect();
			}
			return;
		}
	}
	for (std::vector<Button*>::iterator i = directionButtons.begin(); i != directionButtons.end(); ++i) {
		//(**i).unselect();
		if ((**i).checkClick(mousePosition)) {
			for (std::vector<Button*>::iterator j = directionButtons.begin(); j != directionButtons.end(); ++j) {
				if (j != i)
					(**j).unselect();
			}
			return;
		}
	}

	if (endButton->checkClick(mousePosition)) {
		std::string msjGenerated = generateButtonsString();
		if (msjGenerated[0] == 'w') {
			intergerPosition direction;
			switch (msjGenerated[2]){
			case 'r':
				direction.x = 1;
				direction.y = 0;
				break;
			case 'l':
				direction.x = -1;
				direction.y = 0;
				break;
			case 'u':
				direction.x = 0;
				direction.y = -1;
				break;
			case 'd':
				direction.x = 0;
				direction.y = 1;
				break;
			default:
				break;
			}

			if (ourMap->canMove(ourPlayer->getPosition().x + direction.x, ourPlayer->getPosition().y + direction.y)) {
				socket->send(msjGenerated.c_str(),msjGenerated.length());
				//ourPlayer->move(intergerPosition(ourPlayer->getPosition().x + direction.x, ourPlayer->getPosition().y + direction.y));
			}
		}
		endButton->unselect();

	}
}


std::string HUD::generateButtonsString() {
	std::string ret="";
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		ret += (**it).isClicked();
	}
	ret += "_";
	for (std::vector<Button*>::iterator it = directionButtons.begin(); it != directionButtons.end(); ++it) {
		ret += (**it).isClicked();
	}

	return ret;
}

HUD::HUD(sf::TcpSocket* sock) {
	socket = sock;

	//Font
	if (!font.loadFromFile("calibril.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	//HUD
	sf::RectangleShape* hudSeparator= new sf::RectangleShape(sf::Vector2f(800, 5));
	hudSeparator->setFillColor(sf::Color(200, 200, 200, 255));
	hudSeparator->setPosition(0, 100);
	rectangulos.push_back(hudSeparator);

	sf::RectangleShape* objectsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	objectsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	objectsSeparator->setPosition(200, 0);
	rectangulos.push_back(objectsSeparator);

	sf::RectangleShape* actionsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	actionsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	actionsSeparator->setPosition(350, 0);
	rectangulos.push_back(actionsSeparator);
	
	sf::RectangleShape* buttonsSeparator = new sf::RectangleShape(sf::Vector2f(5, 100));
	buttonsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255));
	buttonsSeparator->setPosition(650, 0);
	rectangulos.push_back(buttonsSeparator);

	sf::RectangleShape* subActionsSeparator = new sf::RectangleShape(sf::Vector2f(300,5));
	subActionsSeparator->setOutlineColor(sf::Color(200, 200, 200, 255)); 
	subActionsSeparator->setPosition(350, 48);
	rectangulos.push_back(subActionsSeparator);

	sf::RectangleShape* subActionsSeparator1 = new sf::RectangleShape(sf::Vector2f(5, 100));
	subActionsSeparator1->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator1->setPosition(425, 0);
	rectangulos.push_back(subActionsSeparator1);

	sf::RectangleShape* subActionsSeparator2 = new sf::RectangleShape(sf::Vector2f(5, 100));
	subActionsSeparator2->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator2->setPosition(500, 0);
	rectangulos.push_back(subActionsSeparator2);

	sf::RectangleShape* subActionsSeparator3 = new sf::RectangleShape(sf::Vector2f(5, 100));
	subActionsSeparator3->setOutlineColor(sf::Color(200, 200, 200, 255));
	subActionsSeparator3->setPosition(575, 0);
	rectangulos.push_back(subActionsSeparator3);

	//textos

	sf::Text* objetosText = new sf::Text("OBJETOS", font, 24);
	objetosText->setFillColor(sf::Color(220, 220, 220, 255));
	objetosText->setStyle(sf::Text::Bold);
	objetosText->setPosition(10, 10);
	texts.push_back(objetosText);

	sf::Text* actionsText = new sf::Text("ACCIONES", font, 24);
	actionsText->setFillColor(sf::Color(220, 220, 220, 255));
	actionsText->setStyle(sf::Text::Bold);
	actionsText->setPosition(210, 20);
	texts.push_back(actionsText);

	//Botones
	endButton = new Button((std::string)"END TURN",(std::string)"",sf::Vector2f(655,10),sf::Vector2f(140,80),font,24);
	
	Button* moveButton = new Button((std::string)"MOVE", (std::string)"w", sf::Vector2f(355, 0), sf::Vector2f(70, 48), font, 18);
	buttons.push_back(moveButton);

	Button* attackButton = new Button((std::string)"ATTACK", (std::string)"a", sf::Vector2f(430, 0), sf::Vector2f(70, 48), font, 18);
	buttons.push_back(attackButton);

	Button* searchButton = new Button((std::string)"SEARCH", (std::string)"s", sf::Vector2f(505, 0), sf::Vector2f(70, 48), font, 18);
	buttons.push_back(searchButton);

	Button* blockButton = new Button((std::string)"BLOCK", (std::string)"b", sf::Vector2f(580, 0), sf::Vector2f(70, 48), font, 18);
	buttons.push_back(blockButton);


	Button* rightButton = new Button((std::string)"LEFT", (std::string)"l", sf::Vector2f(355, 52), sf::Vector2f(70, 48), font, 18);
	directionButtons.push_back(rightButton);

	Button* leftButton = new Button((std::string)"RIGHT", (std::string)"r", sf::Vector2f(430, 52), sf::Vector2f(70, 48), font, 18);
	directionButtons.push_back(leftButton);

	Button* upButton = new Button((std::string)"UP", (std::string)"u", sf::Vector2f(505, 52), sf::Vector2f(70, 48), font, 18);
	directionButtons.push_back(upButton);

	Button* downButton = new Button((std::string)"DOWN", (std::string)"d", sf::Vector2f(580, 52), sf::Vector2f(70, 48), font, 18);
	directionButtons.push_back(downButton);

	//buttons.push_back(endTurnButton);



}


HUD::~HUD() {
	rectangulos.clear();
}