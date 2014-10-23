//==========================//
// RadioRadioButton.cpp     //
// Author: Matthew Stephens //
//==========================//
#include "RadioButton.h"
#include <fstream>


RadioButton::RadioButton(const sf::Font& f, int nOptions):
	font(f),
	nOptions(nOptions)
{

}

// Accessors
int RadioButton::getSelected()
{
	return selected;
}


// Mutators
void RadioButton::setSelected(int sel)
{
	selected = sel;
}

void RadioButton::init()
{
	optButtons = new sf::CircleShape[nOptions];
	optNames = new sf::Text[nOptions];
}

void RadioButton::setPosition(sf::Vector2f p)
{
	pos = p;
	updatePositions();
}

void RadioButton::setTitle(std::string str, int charSize)
{
	title.setFont(font);
	title.setString(str);
	title.setCharacterSize(charSize);
	title.setColor(sf::Color::Black);




	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin(bounds.left, bounds.top);
}

void RadioButton::setOption(std::string str, int charSize, int index)
{
	optNames[index].setFont(font);
	optNames[index].setString(str);
	optNames[index].setCharacterSize(charSize);
	optNames[index].setColor(sf::Color::Black);

	optButtons[index] = sf::CircleShape(0.4f * charSize);
	optButtons[index].setFillColor(sf::Color::White);
}


// Methods

void RadioButton::handleInput(Input *input)
{
	if (input->wasPressed(InputNS::LEFT))
	{
		sf::Vector2f mousePos = input->getMousePos();

		for (int i = 0; i < nOptions; i++)
			if (optButtons[i].getGlobalBounds().contains(mousePos))
			{
				selected = i;
				break;
			}
	}
}

void RadioButton::update(float dt)
{
	for (int i = 0; i < nOptions; i++)
	{
		if (selected == i)
			optButtons[i].setFillColor(sf::Color::Black);
		else
			optButtons[i].setFillColor(sf::Color::White);
	}
}

void RadioButton::draw(sf::RenderWindow& window)
{
	window.draw(title);
	for (int i = 0; i < nOptions; i++)
	{
		window.draw(optButtons[i]);
		window.draw(optNames[i]);
	}
	//window.draw(selCircle);
}

// Helpers

void RadioButton::updatePositions()
{
	// RadioButton's origin is top left corner
	title.setOrigin(0.0f, 0.0f);
	title.setPosition(pos);

	sf::Vector2f tempPos = pos + sf::Vector2f(0.0f, 1.4f * title.getCharacterSize()); 
	for (int i = 0; i < nOptions; i++)
	{
		optButtons[i].setPosition(tempPos);
		//optNames[i].setOrigin(0.0f, 0.0f);
		optNames[i].setPosition(tempPos.x + 1.1f * optNames[i].getCharacterSize(), tempPos.y - 0.167f * optNames[i].getCharacterSize());
		tempPos += sf::Vector2f(0.0f, 1.4f * optNames[i].getCharacterSize());
	}



}