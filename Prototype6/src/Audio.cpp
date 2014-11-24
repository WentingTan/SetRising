//==========================//
// Audio.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Audio.h"
#include "EventManager.h"
#include "Constants.h"

const char *Audio::TRACK_NAMES[NUM_TRACKS] =
{
		"title.wav",
		"track1.wav",
		"track2.wav"
};


void APlayerShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_SHOOT)
	{
		switch (e.weaponType)
		{
		case W_LASER:
			pA->playSound(LASER_S);
			break;
		case W_FREEZE_RAY:
			pA->playSound(FREEZERAY);
			break;
		default:
			break;
		}
	}
}

void AEnemyShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_SHOOT)
		pA->playSound(ENEMY_SHOOT);
}

void APlayerHitHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_HIT)
		pA->playSound(PLAYER_HIT);
}

void AEnemyHitHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_HIT)
	{
		switch (e.enemyType)
		{
		case E_PATROLLING_SNAKE:
		case E_STATIONARY_SNAKE:
			pA->playSound(LG_ENEMY_HIT);
			break;
		default:
			break;
		}
	}
}

void AGBImplodeHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::GRAV_BOMB_IMPLODE)
		pA->playSound(GB_IMPLODE);
}

void APlayerPickupHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_PICKUP)
	{
		switch (e.pickupType)
		{
		case P_HEALTH:
			pA->playSound(PLAYER_HEAL);
			break;
		case P_GRAV_BOMB:
		case P_FLAME_E:
		case P_FREEZE_E:
			pA->playSound(PLAYER_PICKUP);
			break;
		case P_FLAMETHROWER:
		case P_FREEZERAY:
			pA->playSound(GET_WEAPON);
			break;
		default:
			break;
		}
	}
}


void AEDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH)
	{
		switch (e.enemyType)
		{
		case E_PATROLLING_SNAKE:
		case E_STATIONARY_SNAKE:
			pA->playSound(LG_ENEMY_DEATH);
			break;
		case E_WAIT_BAT:
		case E_DIVE_BAT:
		case E_CRAWLER:
			pA->playSound(SM_ENEMY_DEATH);
			break;
		default:
			break;
		}
	}
}

void APlayerDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_DEATH)
		pA->playSound(PLAYER_DEATH);
}

void AEnemyFrozenHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_FROZEN)
		pA->playSound(ENEMY_FREEZE);
}

void AMusicCommandHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::MUSIC_COMMAND)
	{
		switch (e.command)
		{
		case PLAY_SONG:
			pA->playSong(e.track);
			break;
		case PAUSE_MUSIC:
			pA->pauseMusic();
			break;
		case RESUME_MUSIC:
			pA->resumeMusic();
			break;
		default:
			break;
		}
	}
}

Audio::Audio()
{
	sBuffers = NULL;
	sounds = NULL;
	tracks = NULL;

	pShootHandler = NULL;
	eShootHandler = NULL;
	pHitHandler = NULL;
	eHitHandler = NULL;
	implodeHandler = NULL;
	pickupHandler = NULL;
	pDeathHandler = NULL;
	eDeathHandler = NULL;
	frozenHandler = NULL;
	commandHandler = NULL;
}

// Destructor
// Releases any allocated memory
Audio::~Audio()
{
	if (sBuffers)
		delete [] sBuffers;
	if (sounds)
		delete [] sounds;
	if (tracks)
		delete [] tracks;

	if (pShootHandler)
		delete pShootHandler;
	if (eShootHandler)
		delete eShootHandler;
	if (pHitHandler)
		delete pHitHandler;
	if (eHitHandler)
		delete eHitHandler;
	if (implodeHandler)
		delete implodeHandler;
	if (pickupHandler)
		delete pickupHandler;
	if (pDeathHandler)
		delete pDeathHandler;
	if (eDeathHandler)
		delete eDeathHandler;
	if (frozenHandler)
		delete frozenHandler;
	if (commandHandler)
		delete commandHandler;
}

//===
// init()
// Loads and sets sound buffers
//====
void Audio::init()
{
	sBuffers = new sf::SoundBuffer[NUM_SOUNDS];
	sounds = new sf::Sound[NUM_SOUNDS];

	tracks = new sf::Music[NUM_TRACKS];

	playSong(TITLE_MUSIC);

	sBuffers[PLAYER_HIT].loadFromFile(PLAYER_HIT_SB);
	sBuffers[PLAYER_DEATH].loadFromFile(PLAYER_DEATH_SB);
	sBuffers[PLAYER_HEAL].loadFromFile(PLAYER_HEAL_SB);
	sBuffers[PLAYER_PICKUP].loadFromFile(PLAYER_PICKUP_SB);
	sBuffers[LASER_S].loadFromFile(LASER_SB);
	sBuffers[FREEZERAY].loadFromFile(FREEZERAY_SB);
	sBuffers[GB_IMPLODE].loadFromFile(GB_IMPLODE_SB);
	sBuffers[GET_WEAPON].loadFromFile(GET_WEAPON_SB);
	sBuffers[ENEMY_SHOOT].loadFromFile(ENEMY_SHOOT_SB);
	sBuffers[SM_ENEMY_DEATH].loadFromFile(SM_ENEMY_DEATH_SB);
	sBuffers[LG_ENEMY_DEATH].loadFromFile(LG_ENEMY_DEATH_SB);
	sBuffers[LG_ENEMY_HIT].loadFromFile(LG_ENEMY_HIT_SB);
	sBuffers[ENEMY_FREEZE].loadFromFile(ENEMY_FREEZE_SB);
	sBuffers[JUMP].loadFromFile(JUMP_SB);

	for (int i = 0; i < NUM_SOUNDS; i++)
		sounds[i].setBuffer(sBuffers[i]);

	// Create Event Handlers
	pShootHandler = new APlayerShootHandler(this);
	eShootHandler = new AEnemyShootHandler(this);
	pHitHandler = new APlayerHitHandler(this);
	eHitHandler = new AEnemyHitHandler(this);
	implodeHandler = new AGBImplodeHandler(this);
	pickupHandler = new APlayerPickupHandler(this);
	pDeathHandler = new APlayerDeathHandler(this);
	eDeathHandler = new AEDeathHandler(this);
	frozenHandler = new AEnemyFrozenHandler(this);
	commandHandler = new AMusicCommandHandler(this);
}

void Audio::playSound(int soundID)
{
	sounds[soundID].play();
}

void Audio::playSong(int trackID)
{
	if (tracks[current].getStatus() == sf::SoundSource::Playing)
		tracks[current].stop();
	current = trackID;
	tracks[current].openFromFile(TRACK_NAMES[current]);
	tracks[current].play();
}

void Audio::pauseMusic()
{
	tracks[current].pause();
}

void Audio::resumeMusic()
{
	tracks[current].play();
}

void Audio::update()
{
	if (current != TITLE_MUSIC)
	{
		if (tracks[current].getStatus() == sf::SoundSource::Stopped)
		{
			current = (current + 1) % NUM_TRACKS;
			if (current == TITLE_MUSIC)
				current++;
			playSong(current);
		}
	}
}

void Audio::registerHandlers()
{
	EventManager::addHandler(Event::PLAYER_SHOOT, pShootHandler);
	EventManager::addHandler(Event::ENEMY_SHOOT, eShootHandler);
	EventManager::addHandler(Event::PLAYER_HIT, pHitHandler);
	EventManager::addHandler(Event::ENEMY_HIT, eHitHandler);
	EventManager::addHandler(Event::GRAV_BOMB_IMPLODE, implodeHandler);
	EventManager::addHandler(Event::PLAYER_PICKUP, pickupHandler);
	EventManager::addHandler(Event::PLAYER_DEATH, pDeathHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, eDeathHandler);
	EventManager::addHandler(Event::ENEMY_FROZEN, frozenHandler);
	EventManager::addHandler(Event::MUSIC_COMMAND, commandHandler);
}