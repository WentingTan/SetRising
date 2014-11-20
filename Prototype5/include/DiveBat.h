//==========================//
// DiveBat.h                //
// Author: Matthew Stephens //
//==========================//
#ifndef _DIVE_BAT_H_
#define _DIVE_BAT_H_

#include "BatEnemy.h"

class DiveBat : public BatEnemy
{
public:
	// Constructor
	DiveBat();
	// Destructor
	virtual ~DiveBat();

	void activate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	bool update(float dt, sf::Vector2f pPos);
    void copy(DiveBat& e);

protected:
	bool dive;
	sf::Vector2f diveDir;
};

#endif