//==========================//
// PauseMenuState.cpp        //
// Author: Gilbert Colón    //
//==========================//
#include "PauseMenuState.h"
#include "Game.h"

//================================
// Constructor
//================================
PauseMenuState::PauseMenuState(Game *game) :
GameState(game)
{

}

//==============================
// Destructor
//==============================
PauseMenuState::~PauseMenuState()
{

}

// Methods
bool PauseMenuState::init()
{
	return true;
}

void PauseMenuState::handleInput(Input *input)
{

}

void PauseMenuState::update(float dt)
{

}

void PauseMenuState::draw(sf::RenderWindow& window)
{
	//Load menu image
	texture.loadFromFile("CroppedSimplePauseMenu.png");
	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setScale(0.60f, 0.60f);
	sprite.setPosition(250, 50);
	window.draw(sprite);
}