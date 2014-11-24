//==========================//
// Bat.cpp                  //
// Author: Matthew Stephens //
//==========================//
#include "Bat.h"

#include <fstream>
#include "AlphaOscillator.h"
#include "Event.h"
#include "EventManager.h"
#include "Constants.h"
#include "TileMap.h"


Bat::Bat(int type):
	Enemy(type, BAT_HEALTH)
{
	speed = BAT_SPEED;
}

Bat::~Bat()
{
	// Do nothing
}

void Bat::init()
{
	Enemy::init(BAT_FILE);
}