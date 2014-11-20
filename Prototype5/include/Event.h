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
	const int PLAYER_HEAL = 7;
	const int TM_TRANSITION = 8;
	const int NEW_MAP = 9;
	const int DESPAWN_ENEMY = 10;
	const int PLAYER_MOVED = 11;
	const int INITIAL_ENEMY_SPAWN = 12;
	const int GRAV_BOMB_IMPLODE = 13;
	const int RESET_GRAV_BOMB = 14;
	const int GRAV_PICKUP = 15;
	const int NUM_TYPES = 16;

	typedef struct DataStruct
	{
		int type;

		union
		{
			int enemyType;
			int entrance;
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
			float dir;
			float health;
			float damage;
		};

		union
		{
			int reposition;
			int weaponType;
		};
		

		void *map;

		sf::Vector2i tile;

	} Data;
};

#endif