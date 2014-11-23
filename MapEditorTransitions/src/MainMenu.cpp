//==========================//
// MainMenu.cpp             //
// Author: Matthew Stephens //
//==========================//
#include "MainMenu.h"
#include <fstream>

MainMenu::MainMenu(const sf::Font& f, MapEditor *m):
	AppState(f, m)
{
	// Do nothing
}

// Methods
void MainMenu::init()
{
	// Initialize title text
	title.setFont(font);
	title.setString("Map Editor");
	title.setCharacterSize(35);
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	title.setPosition(500.0f, 150.0f);

	// Initialize the New Map button
	sf::Vector2f size;
	size.x = 200.0f;
	size.y = 75.0f;
	std::string str = "New Map";
	newMap.setSize(size);
	newMap.setText(font, str, 20);
	newMap.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	newMap.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	newMap.setOutline(1, sf::Color::Black);
	newMap.setActive(true);
	newMap.setPosition(sf::Vector2f(240.0f, 275.0f));

	// Initialize the Load Map button
	str = "Load Map";
	loadMap.setSize(size);
	loadMap.setText(font, str, 20);
	loadMap.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	loadMap.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(100,100,100), sf::Color(100,100,100));
	loadMap.setOutline(1, sf::Color::Black);
	loadMap.setActive(true);
	loadMap.setPosition(sf::Vector2f(560.0f, 275.0f));
}

void MainMenu::handleInput(Input *input)
{
	newMap.handleInput(input);
	loadMap.handleInput(input);
}

void MainMenu::update(float dt)
{
	if (newMap.wasClicked())
		app->requestStateChange(States::CREATE_NEW);
	else if (loadMap.wasClicked())
		app->requestStateChange(States::LOAD_FROM_FILE);
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(title);
	newMap.draw(window);
	loadMap.draw(window);
}