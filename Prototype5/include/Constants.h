//==========================//
// Constants.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

const float SCREEN_WIDTH = 640.0f;
const float SCREEN_HEIGHT = 480.0f;

const int TILE_SIZE = 32;

// Tile Map Scroll Boundaries
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 1;
const int TOP_EDGE = 3;
const int BOTTOM_EDGE = 4;

// Player Reposition Upon Entering New Tile Map
const int MAINTAIN_X = 0;
const int MAINTAIN_Y = 1;
const int CENTER_TILE = 2;

// Player Weapon Types
const int W_LASER = 0;
const int W_FREEZE_RAY = 1;

const int MAX_LASERS = 8;
const int MAX_FREEZE_RAYS = 6;

// Enemy Weapons Types
const int W_ACID_SPIT = 0;
const int MAX_ACID_SPITS = 16;

// Enemy Types
const int MAX_PATROLLING_SNAKES = 16;
const int MAX_STATIONARY_SNAKES = 16;

const int E_NONE = 0;
const int E_PATROLLING_SNAKE = 1;
const int E_STATIONARY_SNAKE = 2;

const float SNAKE_SPEED = 125.0f;
const int SNAKE_HEALTH = 35;

const int SNAKE_DAMAGE = 5;
const int SNAKE_FRAMES = 4;
const float SNAKE_FRAME_TIME = 0.225f;

const float PS_SHOOT_TIME_LO = 2.0f;
const float PS_SHOOT_TIME_HI = 2.5f;

const int SS_NUM_SHOTS_IN_BURST = 3;
const float SS_BURST_TIME = 0.75f;
const float SS_SHOOT_TIME_LO = 2.0f;
const float SS_SHOOT_TIME_HI = 2.75f;

// Directions
const float D_RIGHT = 1.0f;
const float D_LEFT = -1.0f;

const float E_SPEED = 125.0f;

#endif