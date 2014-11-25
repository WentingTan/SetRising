//==========================//
// HUD.cpp                  //
// Author: Matthew Stephens //
//==========================//
#include "HUD.h"
#include "Constants.h"
#include "EventManager.h"


const sf::IntRect HUD::HBAR_RECT = sf::IntRect(0, 0, 128, 16);
const sf::IntRect HUD::FLM_BAR_RECT = sf::IntRect(0, 0, 78, 16);
const sf::IntRect HUD::FRZ_BAR_RECT = sf::IntRect(0, 16, 78, 16);
const sf::IntRect HUD::FLM_ICON_RECT = sf::IntRect(32, 32, 32, 32);
const sf::IntRect HUD::FRZ_ICON_RECT = sf::IntRect(0, 32, 32, 32);
const sf::IntRect HUD::GRAV_ICON_RECT = sf::IntRect(0, 64, 32, 32);


void HUDHitHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_HIT)
		pH->setEnergy(HEALTH_BAR, e.energy);
}

void HUDPickupHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_PICKUP)
		pH->setEnergy(e.pickupType, e.energy);
}

void HUDContinueHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::CONTINUE)
	{
		pH->setEnergy(HEALTH_BAR, MAX_HEALTH);
		pH->setEnergy(GRAV_BOMBS, MAX_GRAV_BOMBS);
		pH->setEnergy(FLAME_BAR, MAX_FLAME_ENERGY);
		pH->setEnergy(FREEZE_BAR, MAX_FREEZE_ENERGY);
		pH->selectWeapon(W_LASER);
	}
}

void HUDShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_SHOOT)
	{
		switch(e.weaponType)
		{
		case W_GRAVITY_BOMB:
			pH->setEnergy(GRAV_BOMBS, e.energy);
			break;
		case W_FREEZE_RAY:
			pH->setEnergy(FREEZE_BAR, e.energy);
			break;
		case W_FLAMETHROWER:
			pH->setEnergy(FLAME_BAR, e.energy);
			break;
		default:
			break;
		}
	}
}

void HUDWeapSelHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::WEAPON_SEL)
		pH->selectWeapon(e.weaponType);
}


//====================================================
// HUD Constructor
// Initializes the health and and weapon energy bars.
//====================================================
HUD::HUD():
	healthBar(MAX_HEALTH),
	flameEnergy(MAX_FLAME_ENERGY),
	freezeEnergy(MAX_FREEZE_ENERGY)
{
	wSelHandler = NULL;
	shootHandler = NULL;
	hitHandler = NULL;
	pickupHandler = NULL;
	continueHandler = NULL;
}

HUD::~HUD()
{
	if (wSelHandler)
		delete wSelHandler;
	if (shootHandler)
		delete shootHandler;
	if (hitHandler)
		delete hitHandler;
	if (pickupHandler)
		delete pickupHandler;
	if (continueHandler)
		delete continueHandler;
}

void HUD::init(sf::Texture *h, sf::Texture *w, sf::Texture *g)
{
	healthBar.setTexture(h);
	healthBar.setTextureRect(HBAR_RECT);
	healthBar.setColor(sf::Color::Red);
	healthBar.setPosition(HEALTH_POS_X, HEALTH_POS_Y);

	flameEnergy.setTexture(w);
	flameEnergy.setTextureRect(FLM_BAR_RECT);
	flameEnergy.setColor(sf::Color(224, 128, 64));
	flameEnergy.setPosition(WEAPON_ENERGY_POS_X, WEAPON_ENERGY_POS_Y);

	freezeEnergy.setTexture(w);
	freezeEnergy.setTextureRect(sf::IntRect(0, 16, 78, 16));
	freezeEnergy.setColor(sf::Color(67, 141, 217));
	freezeEnergy.setPosition(WEAPON_ENERGY_POS_X, WEAPON_ENERGY_POS_Y);

	flameIcon.setTexture(*w);
	flameIcon.setTextureRect(FLM_ICON_RECT);
	flameIcon.setPosition(HEALTH_POS_X - 32.0f, HEALTH_POS_Y);

	freezeIcon.setTexture(*w);
	freezeIcon.setTextureRect(FRZ_ICON_RECT);
	freezeIcon.setPosition(HEALTH_POS_X - 32.0f, HEALTH_POS_Y);

	gravIcon.setTexture(*w);
	gravIcon.setTextureRect(GRAV_ICON_RECT);
	gravIcon.setPosition(HEALTH_POS_X - 32.0f, HEALTH_POS_Y);

	gravBomb.setTexture(*g);
	sf::FloatRect bounds = gravBomb.getLocalBounds();
	gravBomb.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	gravBomb.setScale(0.8f, 0.8f);


	wSelect = W_LASER;
	nGravBombs = MAX_GRAV_BOMBS;

	// Create and register event handlers
	shootHandler = new HUDShootHandler(this);
	hitHandler = new HUDHitHandler(this);
	pickupHandler = new HUDPickupHandler(this);
	wSelHandler = new HUDWeapSelHandler(this);
	continueHandler = new HUDContinueHandler(this);

	EventManager::addHandler(Event::PLAYER_SHOOT, shootHandler);
	EventManager::addHandler(Event::PLAYER_HIT, hitHandler);
	EventManager::addHandler(Event::PLAYER_PICKUP, pickupHandler);
	EventManager::addHandler(Event::WEAPON_SEL, wSelHandler);
	EventManager::addHandler(Event::CONTINUE, continueHandler);
}

void HUD::setEnergy(int type, float amount)
{
	switch (type)
	{
	case HEALTH_BAR:
		healthBar.setEnergy(amount);
		break;
	case GRAV_BOMBS:
		nGravBombs = (int)amount;
		break;
	case FLAME_BAR:
		flameEnergy.setEnergy(amount);
		break;
	case FREEZE_BAR:
		freezeEnergy.setEnergy(amount);
		break;
	default:
		break;
	}
}

void HUD::selectWeapon(int weapon)
{
	wSelect = weapon;
}

void HUD::draw(sf::RenderWindow& window)
{
	healthBar.draw(window);

	if (wSelect == W_GRAVITY_BOMB)
	{
		window.draw(gravIcon);

		sf::FloatRect bounds = gravBomb.getGlobalBounds();
		gravBomb.setPosition(WEAPON_ENERGY_POS_X + 12.0f, WEAPON_ENERGY_POS_Y + 8.0f);
		for (int i = 0; i < nGravBombs; i++)
		{
			window.draw(gravBomb);
			gravBomb.move(bounds.width + 8.0f, 0.0f);
		}
	}

	if (wSelect == W_FLAMETHROWER)
	{
		window.draw(flameIcon);
		flameEnergy.draw(window);
	}
	else if (wSelect == W_FREEZE_RAY)
	{
		window.draw(freezeIcon);
		freezeEnergy.draw(window);
	}
}
