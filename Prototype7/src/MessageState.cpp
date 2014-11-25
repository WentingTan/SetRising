//==========================//
// MessageState.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "MessageState.h"
#include "Constants.h"
#include "Game.h"
#include "EventManager.h"

const sf::IntRect MessageState::FLAME_RECT = sf::IntRect(0, 0, 220, 128);
const sf::IntRect MessageState::FREEZE_RECT = sf::IntRect(0, 128, 220, 128);
const float MessageState::MESSAGE_TIME = 4.5f;
const float MessageState::EXPAND_TIME = 0.25f;
const float MessageState::MIN_SCALE = 0.1f;

//================================
// Constructor
//================================
MessageState::MessageState(Game *game, int type):
	GameState(game),
	type(type)
{
	// Do nothing
}

//==============================
// Destructor
//==============================
MessageState::~MessageState()
{

}

// Methods
bool MessageState::init()
{
	message.setTexture(*(pGame->getTexture(SCREENS)));
	
	switch (type)
	{
	case MSG_GOT_FLAME:
		message.setTextureRect(FLAME_RECT);
		break;
	case MSG_GOT_FREEZE:
		message.setTextureRect(FREEZE_RECT);
		break;
	default:
		break;
	}

	sf::FloatRect bounds = message.getLocalBounds();
	message.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	message.setPosition(0.5f * SCREEN_WIDTH, 0.5f * SCREEN_HEIGHT);
	message.setScale(MIN_SCALE, MIN_SCALE);

	timer = 0.0f;

	Event::Data e;
	e.type = Event::MUSIC_COMMAND;
	e.command = PAUSE_MUSIC;
	EventManager::triggerEvent(e);

	return true;
}

void MessageState::handleInput(Input *input)
{
	// Do nothing
}

void MessageState::update(float dt)
{
	timer += dt;

	if (timer > MESSAGE_TIME)
	{
		pGame->requestStateChange(GSCR_POP);
		Event::Data e;
		e.type = Event::MUSIC_COMMAND;
		e.command = RESUME_MUSIC;
		EventManager::triggerEvent(e);
	}
	else if (timer > EXPAND_TIME)
		message.setScale(1.0f, 1.0f);
	else
	{
		float scale = MIN_SCALE + ((1.0f - MIN_SCALE) / EXPAND_TIME) * timer;
		message.setScale(scale, scale);
	}
}

void MessageState::draw(sf::RenderWindow& window)
{
	window.draw(message);
}