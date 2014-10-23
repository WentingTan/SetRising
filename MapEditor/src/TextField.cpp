//==========================//
// TextField.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "TextField.h"
#include <fstream>

//=========================================================
// Constructor(const sf::Font&, std::string, int, int)
//
//==========================================================
TextField::TextField(const sf::Font& f, std::string n, int charSize, int charLimit):
	charSize(charSize),
	charLimit(charLimit),
	active(false),
	padding(20.0f)
{
	// Initialize the text object holding the name of the text field
	name.setFont(f);
	name.setString(n);
	name.setCharacterSize(charSize);
	name.setColor(sf::Color::Black);
	sf::FloatRect bounds = name.getLocalBounds();
	name.setOrigin(bounds.left, bounds.top);

	// Initialize the text object that will hold entered text
	entered.setFont(f);
	entered.setString("");
	entered.setCharacterSize(charSize);
	entered.setColor(sf::Color::Black);
	bounds = entered.getLocalBounds(); 
	entered.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

	// Initalize the RectangleShape acting as the text box
	sf::Vector2f textAreaSize;
	textAreaSize.y = 1.2f * charSize;
	textAreaSize.x = 1.05f * charSize * charLimit;
	textArea.setSize(textAreaSize);
	textArea.setOrigin(textAreaSize.x / 2.0f, textAreaSize.y / 2.0f);

	// Initialize the RectanlgeShape acting as the cursor
	cursor.setSize(sf::Vector2f(2.0f, 1.05f * charSize));
	cursor.setFillColor(sf::Color::Black);
	cursor.setOrigin(0.0f, cursor.getLocalBounds().height / 2.0f);

	// Set an initial position of (0,0)
	setPosition(sf::Vector2f(0.0f, 0.0f));
}

//=====================================================================================
// setPosition(sf::Vector2f)
// Sets the position of the upper left corner of the text field. Updates the positions
// of all component parts.
//=====================================================================================
void TextField::setPosition(sf::Vector2f p)
{
	pos = p;
	updatePositions();
}

//=============================================================
// setTextColor(sf::Color)
// Sets the color of the text field name and the entered text.
//=============================================================
void TextField::setTextColor(sf::Color color)
{
	name.setColor(color);
	entered.setColor(color);
}

//==================================================================
// setTextAreaOutline(int, sf::Color)
// Sets the thickness and color of the outline around the text box.
//==================================================================
void TextField::setTextAreaOutline(int thickness, sf::Color color)
{
	textArea.setOutlineThickness(thickness);
	textArea.setOutlineColor(color);
}

//==============================================================
// setEnteredText(std::string)
// Sets the text appearing in the text box to the given string.
//==============================================================
void TextField::setEnteredText(std::string text)
{
	entered.setString(text);
	updatePositions();
}

//===
// handleInput(Input*)
//===
void TextField::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();

	if (input->wasPressed(InputNS::LEFT))
	{
		if (textArea.getGlobalBounds().contains(mousePos))
			active = true;
		else
			active = false;
	}

	//if (textArea.getGlobalBounds().contains(mousePos))
		//if (input->wasPressed(InputNS::LEFT))
			//active = true;

	if (active)
	{
		char c;
		if (input->getTextIn(c))
			addChar(c);

		if (input->getBackspace())
			deleteChar();
	}

}

//=========================================================================
// draw(sf::RenderWindow&)
// Draws all of the component parts of the text field to the given window.
//=========================================================================
void TextField::draw(sf::RenderWindow& window)
{
	window.draw(name);
	window.draw(textArea);
	// If the text field is inactive, the cursor is not drawn and the entered
	// text appears gray
	if (active)
	{
		window.draw(cursor);
		entered.setColor(sf::Color::Black);
	}
	else
		entered.setColor(sf::Color(150, 150, 150));
	window.draw(entered);
}

//==============================================================================
// setActive(bool)
// Activates or deactivates the text box. A text box must be active in order to
// receive input.
//==============================================================================
void TextField::setActive(bool a)
{
	active = a;
}

//==========================================================================
// getEnteredText
// Returns a std::string of the text that has been entered in the text box.
//==========================================================================
std::string TextField::getEnteredText()
{
	return entered.getString();
}

//=========//
// Helpers //
//=========//

//====================================================================================
// updatePositions()
// Updates the positions of all the component parts that make up a text field object.
//====================================================================================
void TextField::updatePositions()
{
	name.setPosition(pos);

	// Recalculate origins of text and text box
	sf::FloatRect bounds = textArea.getLocalBounds();
	textArea.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	bounds = entered.getLocalBounds();
	entered.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

	// Calculate and set positions for text box and entered text 
	bounds = name.getGlobalBounds();
	float x = bounds.left + bounds.width + padding + textArea.getLocalBounds().width / 2.0f;
	float y = bounds.top + bounds.height / 2.0f;
	textArea.setPosition(x, y);
	entered.setPosition(x, y);

	// Calculate and set position for the cursor
	bounds = entered.getGlobalBounds();
	x = bounds.left + bounds.width + 3.0f;
	bounds = textArea.getGlobalBounds();
	y = bounds.top + bounds.height / 2.0f;
	cursor.setPosition(x, y);
}

//=========================================================
// addChar(char)
// Adds the given character to the string in the text box.
//=========================================================
void TextField::addChar(char c)
{
	std::string str = entered.getString();
	
	// Do nothing if the string has reached the character limit
	if (str.size() < charLimit)
	{
		str += c;
		entered.setString(str);
		updatePositions();
	}
}

//=====================================================
// deleteChar()
// Deletes the last character entered in the text box.
//=====================================================
void TextField::deleteChar()
{
	std::string str = entered.getString();

	// Do nothing if the string is empty
	if (!str.empty())
	{
		str.erase(str.size() - 1, 1);
		entered.setString(str);
		updatePositions();
	}
}
