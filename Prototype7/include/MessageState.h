//==========================//
// MessageState.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _MESSAGE_STATE_H_
#define _MESSAGE_STATE_H_

#include "GameState.h"


class MessageState : public GameState
{
public:
	// Constructor
	MessageState(Game *game, int type);
	// Destructor
	virtual ~MessageState();

	// Methods
	virtual bool init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

protected:
	sf::Sprite message;
	int type;
	float timer;

	static const sf::IntRect FLAME_RECT;
	static const sf::IntRect FREEZE_RECT;
	static const float MESSAGE_TIME;
	static const float EXPAND_TIME;
	static const float MIN_SCALE;
};

#endif