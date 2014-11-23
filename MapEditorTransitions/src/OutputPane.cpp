//==========================//
// OutputPane.cpp           //
// Author: Matthew Stephens //
//==========================//
#include "OutputPane.h"

OutputPane::OutputPane(const sf::Font& f, TileMap *m):
	saveFile(f, "Save File As", 20, 15),
	bounds(0.0f, 600.0f, 800.0f, 75.0f),
	background(sf::Vector2f(800.0f, 75.0f)),
	font(f),
	map(m)
{
	gridOn = false;
	background.setPosition(0.0f, 601.0f);
	background.setFillColor(sf::Color(225, 225, 225));
	background.setOutlineThickness(1);
	background.setOutlineColor(sf::Color::Black);
}

OutputPane::~OutputPane()
{
}


void OutputPane::init()
{
	// Initialize the saveFile field
	saveFile.setPosition(sf::Vector2f(210.0f, 628.0f));
	saveFile.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the gridToggle button
	sf::Vector2f size;
	size.x = 80.0f;
	size.y = 35.0f;
	std::string str = "Grid On";
	gridToggle.setSize(size);
	gridToggle.setText(font, str, 15);
	gridToggle.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	gridToggle.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	gridToggle.setOutline(1, sf::Color::Black);
	gridToggle.setActive(true);
	gridToggle.setPosition(sf::Vector2f(30.0f, 620.0f));

	// Initialize the save button
	size.x = 80.0f;
	size.y = 35.0f;
	str = "Save";
	save.setSize(size);
	save.setText(font, str, 15);
	save.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	save.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	save.setOutline(1, sf::Color::Black);
	save.setActive(true);
	save.setPosition(sf::Vector2f(695.0f, 620.0f));
	
}

void OutputPane::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();

	if (bounds.contains(mousePos))
	{
		gridToggle.handleInput(input);
		save.handleInput(input);
		saveFile.handleInput(input);
	}
}

void OutputPane::update(float dt)
{
	if (gridToggle.wasClicked())
	{
		if (gridOn)
		{
			std::string str = "Grid On";
			gridToggle.setText(font, str, 15);
			gridOn = false;
		}
		else
		{
			std::string str = "Grid Off";
			gridToggle.setText(font, str, 15);
			gridOn = true;
		}
	}

	if (save.wasClicked())
		map->save(saveFile.getEnteredText());
}

void OutputPane::draw(sf::RenderWindow& window)
{
	window.draw(background);
	gridToggle.draw(window);
	save.draw(window);
	saveFile.draw(window);
}