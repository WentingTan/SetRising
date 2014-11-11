//==========================//
// HealthPickup.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "HealthPickup.h"
#include "AlphaOscillator.h"

HealthPickup::HealthPickup():
	Entity()
{
	// Do nothing
}

//======================================================
// HealthPickup Destructor
// Deallocates space for the fadeFlash AlphaOscillator.
//======================================================
HealthPickup::~HealthPickup()
{
	if (fadeFlash)
		delete fadeFlash;
}

//===========//
// Accessors //
//===========//

//=========================================
// HealthPickup::getHealth()
// Returns the health value of the pickup.
//=========================================
int HealthPickup::getHealth() const
{
	return health;
}

//==================================================================================
// HealthPickup::init()
// Sets the sprite's texture and origin. Initializes the fadeFlash AlphaOscillator.
//==================================================================================
void HealthPickup::init()
{
	sprite.setTexture(*texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	fadeFlash = new AlphaOscillator(HPickup::FD_HI_ALPHA, HPickup::FD_LO_ALPHA, HPickup::FD_CYCLE);
}


//===============================
// HealthPickup::deactivate()
// Deactivates the HealthPickup.
//===============================
void HealthPickup::deactivate()
{
	active = false;
}

//=============================================================================================
// HealthPickup::activate(sf::Vector2f,int,sf::Vector2i)
// Sets the scale factor and position of the sprite and the amount of health received from 
// the pickup ased on the 'size' parameter. Sets the pickup to active, and sets the fade flag,
// which indicates whether or not the item will fade after a given period of time.
//=============================================================================================
void HealthPickup::activate(sf::Vector2f pos, int size, sf::Vector2i tile)
{
	// Set the health value and scale of the sprite depending on the 'size'
	// of the pickup
	if (size == HPickup::SMALL)
	{
		health = HPickup::SM_HEALTH;
		sprite.setScale(1.0f, 1.0f);
	}
	else
	{
		health = HPickup::LG_HEALTH;
		sprite.setScale(2.0f, 2.0f);
	}
	sprite.setColor(sf::Color::White);

	// Set the sprite's position
	sprite.setPosition(pos);

	// Set the hitbox
	hitbox = sprite.getGlobalBounds();

	// Set the active flag to true
	active = true;

	// If the tile index is (0,0), this pickup was generated on an enemy death
	// and will disappear after a given time. If it is a pickup placed in the
	// TileMap by the map editor, then it remains until picked up
	this->tile = tile;
	if (tile.x == 0 && tile.y == 0)
		fade = true;
	else
		fade = false;

	// If this item will disappear, reset the timer and the AlphaOscillator
	if (fade)
	{
		time = 0.0f;
		fadeFlash->reset();
	}
}

//=======================================================================
// HealthPickup::update(float)
// If the pickup is set to disappear after a period of time, this method
// tracks that time and controls the flashing animation of the pickup as
// it fades. Returns true if the pickup has expired.
//=======================================================================
bool HealthPickup::update(float dt)
{
	if (fade)
	{
		time += dt;

		if (time > HPickup::TIME_TILL_FADE + HPickup::FADE_TIME)
			return true;
		else if (time > HPickup::TIME_TILL_FADE)
		{
			fadeFlash->update(dt);
			sprite.setColor(sf::Color(255, 255, 255, fadeFlash->getAlpha()));
		}
	}
	return false;
}

//================================================================================
// HealthPickup::swap(HealthPickup&)
// Swaps all data members between this pickup and the pickup passed by reference.
//================================================================================
void HealthPickup::swap(HealthPickup& hp)
{
	sf::Texture *tmpText = texture;
	sf::Sprite tmpSprite = sprite;
	sf::FloatRect tmpHB = hitbox;
	bool tmpAct = active;
	int tmpHlth = health;
	float tmpTime = time;
	bool tmpFd = fade;
	sf::Vector2i tmpTile = tile;
	AlphaOscillator *tmpFlash = fadeFlash;

	texture = hp.texture;
	sprite = hp.sprite;
	hitbox = hp.hitbox;
	active = hp.active;
	health = hp.health;
	time = hp.time;
	fade = hp.fade;
	tile = hp.tile;
	fadeFlash = hp.fadeFlash;

	hp.texture = tmpText;
	hp.sprite = tmpSprite;
	hp.hitbox = tmpHB;
	hp.active = tmpAct;
	hp.health = tmpHlth;
	hp.time = tmpTime;
	hp.fade = tmpFd;
	hp.tile = tmpTile;
	hp.fadeFlash = tmpFlash;
}

