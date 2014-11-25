//==========================//
// WaitBat.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _WAIT_BAT_H_
#define _WAIT_BAT_H_

#include "Bat.h"

class WaitBat : public Bat
{
public:
	// Constructor
	WaitBat();
	// Destructor
	virtual ~WaitBat();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, sf::Vector2f pPos);
    void copy(WaitBat& e);

protected:
	bool go;
};

#endif