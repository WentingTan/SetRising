//==========================//
// Event.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _EVENT_H
#define _EVENT_H

#include <SFML/Graphics.hpp>

//====================================================================================
// Namespace Event
// Lists the types of events, and defines a struct that contains data about an event.
// Certain fields in the struct are meaningful only for certain event types:
// 
// 1. SPAWN_ENEMY
//		posX, posY: The x and y screen coordinates of the location at which to
//		spawn the enemy.
//		tile: The indices of the tile at which the enemy spawns.
//		dir: The direction that the enemy should face when spawned.
//
// 2. ENEMY_DEATH
//
//
//
//
//
//
//
//
//
namespace Event
{
	const int SPAWN_ENEMY = 0;
	const int ENEMY_DEATH = 1;
	const int SCROLL = 2;
	const int PLAYER_SHOOT = 3;
	const int ENEMY_SHOOT = 4;
	const int ENEMY_HIT = 5;
	const int PLAYER_HIT = 6;
	const int TM_TRANSITION = 7;
	const int NEW_MAP = 8;
	const int DESPAWN_ENEMY = 9;
	const int PLAYER_MOVED = 10;
	const int INITIAL_ENEMY_SPAWN = 11;
	const int GRAV_BOMB_IMPLODE = 12;
	const int RESET_GRAV_BOMB = 13;
	const int GRAV_PICKUP = 14;
	const int WEAPON_SEL = 15;
	const int PLAYER_PICKUP = 16;
	const int SPAWN_WEAPON = 17;
	const int DESPAWN_WEAPON = 18;
	const int CONTINUE = 19;
	const int PLAYER_DEATH = 20;
	const int PLAYER_DEATH_ANIM_DONE = 21;
	const int SPAWN_BARRIER = 22;
	const int DESPAWN_BARRIER = 23;
	const int ENEMY_FROZEN = 24;
	const int MUSIC_COMMAND = 25;
	const int NUM_TYPES = 26;

	typedef struct DataStruct
	{
		int type;

		union
		{
			int enemyType;
			int pickupType;
			int entrance;
			int command;
		};

		union
		{
			float posX;
			float scrollX;
		};

		union
		{
			float posY;
			float scrollY;
		};

		union
		{
			int reposition;
			int weaponType;
			int track;
		};
		
		float dir;
		union
		{
			float energy;
			float damage;
			float health;
		};

		void *map;

		sf::Vector2i tile;

	} Data;
};

#endif