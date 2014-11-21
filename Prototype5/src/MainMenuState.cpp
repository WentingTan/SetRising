//==========================//
// MainMenuState.cpp        //
// Author: Gilbert Colón    //
//==========================//
#include "MainMenuState.h"
#include "Game.h"

//================================
// Constructor
//================================
MainMenuState::MainMenuState(Game *game) :
GameState(game)
{

}

//==============================
// Destructor
//==============================
MainMenuState::~MainMenuState()
{

}

// Methods
bool MainMenuState::init()
{
	return true;
}

void MainMenuState::handleInput(Input *input)
{

}

void MainMenuState::update(float dt)
{

}

void MainMenuState::draw(sf::RenderWindow& window)
{
	//Load menu image
	texture.loadFromFile("SetStartScreen.png");
	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setScale(0.75f, 0.75f);
	window.draw(sprite);
}