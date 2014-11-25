//==========================//
// GravityBomb.h            //
// Author: Matthew Stephens //
//==========================//
#ifndef _GRAVITY_BOMB_H_
#define _GRAVITY_BOMB_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EventHandler.h"

class GravityBomb;

//==================================================
// GravityBomb EventHandler for Event::PLAYER_SHOOT
//==================================================
class GBResetHandler : public EventHandler
{
public:
	// Constructor
	explicit GBResetHandler(GravityBomb *gb): pGB(gb) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	GravityBomb *pGB;
};

class GravityBomb : public Entity
{
public:
	// Constructor
	GravityBomb();
	// Destructor
	~GravityBomb();

	// Accessors
	float getDir() const;
	bool isReady() const;

	// Mutators
	void setReady();

	// Methods
	void init();
	void activate(sf::Vector2f pos, float dir);
    void deactivate();
	void update(float dt);

private:
	float speed;
	float dir;
	float dist;
	bool ready;
	bool imploding;
	float timer;

	EventHandler *resetHandler;
};

#endif