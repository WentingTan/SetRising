//==========================//
// HUD.h                    //
// Author: Matthew Stephens //
//==========================//
#ifndef _HUD_H_
#define _HUD_H_

#include "EnergyBar.h"
#include "EventHandler.h"
#include "Constants.h"

// Forward declaration
class HUD;

//==========================================
// HUD EventHandler for Event::PLAYER_SHOOT
//==========================================
class HUDShootHandler : public EventHandler
{
public:
	// Constructor
	explicit HUDShootHandler(HUD *h): pH(h) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	HUD *pH;
};

//========================================
// HUD EventHandler for Event::PLAYER_HIT
//========================================
class HUDHitHandler : public EventHandler
{
public:
	// Constructor
	explicit HUDHitHandler(HUD *h): pH(h) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	HUD *pH;
};


//=========================================
// HUD EventHandler for Event::WEAPON_SEL
//=========================================
class HUDWeapSelHandler : public EventHandler
{
public:
	// Constructor
	explicit HUDWeapSelHandler(HUD *h): pH(h) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	HUD *pH;
};

//======================================
// HUD EventHandler for Event::CONTINUE
//======================================
class HUDContinueHandler : public EventHandler
{
public:
	// Constructor
	explicit HUDContinueHandler(HUD *h): pH(h) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	HUD *pH;
};

//===========================================
// HUD EventHandler for Event::PLAYER_PICKUP
//===========================================
class HUDPickupHandler : public EventHandler
{
public:
	// Constructor
	explicit HUDPickupHandler(HUD *h): pH(h) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	HUD *pH;
};

class HUD
{
public:
	// Constructor
	HUD();
	// Destructor
	~HUD();

	// Methods
	void init(sf::Texture *h, sf::Texture *w, sf::Texture *g);
	void setEnergy(int type, float amount);
	void selectWeapon(int weapon);
	void draw(sf::RenderWindow& window);

protected:
	EnergyBar healthBar;
	EnergyBar flameEnergy;
	EnergyBar freezeEnergy;
	sf::Sprite flameIcon;
	sf::Sprite freezeIcon;
	sf::Sprite gravIcon;
	sf::Sprite gravBomb;
	int wSelect;
	int nGravBombs;

	EventHandler *hitHandler;
	EventHandler *pickupHandler;
	EventHandler *shootHandler;
	EventHandler *wSelHandler;
	EventHandler *continueHandler;

	static const sf::IntRect HBAR_RECT;
	static const sf::IntRect FLM_BAR_RECT;
	static const sf::IntRect FRZ_BAR_RECT;
	static const sf::IntRect FLM_ICON_RECT;
	static const sf::IntRect FRZ_ICON_RECT;
	static const sf::IntRect GRAV_ICON_RECT;

};

#endif