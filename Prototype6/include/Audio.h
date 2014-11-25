//==========================//
// Audio.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SFML/Audio.hpp>
#include "EventHandler.h"

const char PLAYER_HIT_SB[] = "player_hit.wav";
const char PLAYER_DEATH_SB[] = "player_death.wav";
const char PLAYER_HEAL_SB[] = "player_heal.wav";
const char PLAYER_PICKUP_SB[] = "player_pickup.wav";
const char LASER_SB[] = "laser.wav";
const char FREEZERAY_SB[] = "freeze_ray.wav";
const char GB_IMPLODE_SB[] = "gb_implode.wav";
const char GET_WEAPON_SB[] = "get_weapon.wav";
const char ENEMY_SHOOT_SB[] = "enemy_shoot.wav";
const char SM_ENEMY_DEATH_SB[] = "small_death.wav";
const char LG_ENEMY_DEATH_SB[] = "big_death.wav";
const char LG_ENEMY_HIT_SB[] = "enemy_hit.wav";
const char ENEMY_FREEZE_SB[] = "enemy_freeze.wav";
const char JUMP_SB[] = "jump.wav";

const int PLAYER_HIT = 0;
const int PLAYER_DEATH = 1;
const int PLAYER_HEAL = 2;
const int PLAYER_PICKUP = 3;
const int LASER_S = 4;
const int FREEZERAY = 5;
const int GB_IMPLODE = 6;
const int GET_WEAPON = 7;
const int ENEMY_SHOOT = 8;
const int SM_ENEMY_DEATH = 9;
const int LG_ENEMY_DEATH = 10;
const int LG_ENEMY_HIT = 11;
const int ENEMY_FREEZE = 12;
const int JUMP = 13;
const int NUM_SOUNDS = 14;

// Music
const int NUM_TRACKS = 3;

// Forward declaration
class Audio;

// Event Handlers
//============================================
// Audio EventHandler for Event::PLAYER_SHOOT
//============================================
class APlayerShootHandler : public EventHandler
{
public:
	// Constructor
	explicit APlayerShootHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//===========================================
// Audio EventHandler for Event::ENEMY_SHOOT
//===========================================
class AEnemyShootHandler : public EventHandler
{
public:
	// Constructor
	explicit AEnemyShootHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//==========================================
// Audio EventHandler for Event::PLAYER_HIT
//==========================================
class APlayerHitHandler : public EventHandler
{
public:
	// Constructor
	explicit APlayerHitHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//=========================================
// Audio EventHandler for Event::ENEMY_HIT
//=========================================
class AEnemyHitHandler : public EventHandler
{
public:
	// Constructor
	explicit AEnemyHitHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//=================================================
// Audio EventHandler for Event::GRAV_BOMB_IMPLODE
//=================================================
class AGBImplodeHandler : public EventHandler
{
public:
	// Constructor
	explicit AGBImplodeHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//=============================================
// Audio EventHandler for Event::PLAYER_PICKUP
//=============================================
class APlayerPickupHandler : public EventHandler
{
public:
	// Constructor
	explicit APlayerPickupHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//===========================================
// Audio EventHandler for Event::ENEMY_DEATH
//===========================================
class AEDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit AEDeathHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//===========================================
// Audio EventHandler for Event::PLAYER_DEATH
//===========================================
class APlayerDeathHandler : public EventHandler
{
public:
	// Constructor
	explicit APlayerDeathHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//============================================
// Audio EventHandler for Event::ENEMY_FROZEN
//============================================
class AEnemyFrozenHandler : public EventHandler
{
public:
	// Constructor
	explicit AEnemyFrozenHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

//=============================================
// Audio EventHandler for Event::MUSIC_COMMAND
//=============================================
class AMusicCommandHandler : public EventHandler
{
public:
	// Constructor
	explicit AMusicCommandHandler(Audio *a): pA(a) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Audio *pA;
};

class Audio
{
public:
	// Constructor
	Audio();
	// Destructor
	~Audio();

	// Methods
	void init();
	void registerHandlers();
	void playSound(int soundID);
	void playSong(int trackID);
	void pauseMusic();
	void resumeMusic();
	void update();

private:
	sf::SoundBuffer *sBuffers;
	sf::Sound *sounds;

	sf::Music *tracks;
	char *trackNames[NUM_TRACKS];
	int current;

	EventHandler *pShootHandler;
	EventHandler *eShootHandler;
	EventHandler *pHitHandler;
	EventHandler *eHitHandler;
	EventHandler *implodeHandler;
	EventHandler *pickupHandler;
	EventHandler *eDeathHandler;
	EventHandler *pDeathHandler;
	EventHandler *frozenHandler;
	EventHandler *commandHandler;

	static const char *TRACK_NAMES[NUM_TRACKS]; 
};

#endif