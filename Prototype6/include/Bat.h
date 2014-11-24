//==========================//
// Bat.h                    //
// Author: Matthew Stephens //
//==========================//
#ifndef _BAT_H_
#define _BAT_H_

#include "Enemy.h"

class Bat : public Enemy
{
public:
	// Constructor
	Bat(int type);
	// Destructor
	virtual ~Bat();

	void init();

protected:
	
};

#endif