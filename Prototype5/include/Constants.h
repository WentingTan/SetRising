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

// Background Scaling
const int NO_SCALE = 0;
const int SCALE_TO_HEIGHT = 1;
const int SCALE_TO_WIDTH = 2;

// Player Reposition Upon Entering New Tile Map
const int MAINTAIN_X = 0;
const int MAINTAIN_Y = 1;
const int CENTER_TILE = 2;

// Pickup Constants
const float TIME_TILL_FADE = 3.0f;
const float FADE_TIME = 1.5f;
const float FD_ALPHA_HI = 255.0f;
const float FD_ALPHA_LO = 100.0f;
const float FD_CYCLE = 0.1f;
// Pickup types
const int SM_HEALTH = 0;
const int LG_HEALTH = 1;
const int GRAV_BOMB = 2;

const float LG_HEALTH_VAL = 7.5f;
const float SM_HEALTH_VAL = 3.0f;

const int MAX_HEALTH_PICKUPS = 8;
const int MAX_GRAV_PICKUPS = 8;


// Player Weapon Types
const int W_LASER = 0;
const int W_FREEZE_RAY = 1;
const int W_FLAMETHROWER = 2;
const int W_GRAVITY_BOMB = 3;

const float LASER_DAMAGE = 5.0f;
const float FREEZE_DAMAGE = 7.5f;

const float GRAV_BOMB_SPEED = 300.0f;
const float GB_IMPLODE_TIME = 0.2f;
const float GB_MIN_SCALE = 0.1f;
const float GB_MAX_SCALE = 0.75f;
const float BH_EXPAND_TIME = 0.25f;
const float BH_MIN_SCALE = 0.1f;
const float BH_MAX_SCALE = 2.5f;
const float GRAV_CONST = 5000.0f;

// FLamethrower Animation
const int FLAME_FRAMES = 3;
const float FLAME_FRAME_TIME = 0.125f;
const int FLAME_IMG_WIDTH = 64;
const int FLAME_IMG_HEIGHT = 32;

const float FLAME_HB_WIDTH = 48.0f;
const float FLAME_DAMAGE = 50.0f;
const float FLAME_TIME = 0.5f;
const float FREEZE_TIME = 3.5f;

const float BH_ANG_VEL = 360.0f;
const float BH_TIME = 2.5f;
const int BH_ALPHA = 125;

const int MAX_LASERS = 8;
const int MAX_FREEZE_RAYS = 6;

// Enemy Weapons Types
const int W_ACID_SPIT = 0;
const int MAX_ACID_SPITS = 16;

// Enemy Types
const int MAX_PATROLLING_SNAKES = 16;
const int MAX_STATIONARY_SNAKES = 16;
const int MAX_WAIT_BATS = 8;
const int MAX_DIVE_BATS = 8;
const int MAX_BOSS = 2;
const int E_NONE = 0;
const int E_PATROLLING_SNAKE = 1;
const int E_STATIONARY_SNAKE = 2;
const int E_WAIT_BAT = 3;
const int E_DIVE_BAT = 4;
const int E_BOSS = 5;


const char SNAKE_FILE[] = "snake.txt";
const char BAT_FILE[] = "bat.txt";
const char BOSS_FILE[] = "boss.txt";


const float SNAKE_SPEED = 125.0f;
const float SNAKE_HEALTH = 35.0f;

const int SNAKE_DAMAGE = 5;
const int SNAKE_FRAMES = 4;
const float SNAKE_FRAME_TIME = 0.225f;

const float PS_SHOOT_TIME_LO = 2.0f;
const float PS_SHOOT_TIME_HI = 2.5f;

const int SS_NUM_SHOTS_IN_BURST = 3;
const float SS_BURST_TIME = 0.75f;
const float SS_SHOOT_TIME_LO = 2.0f;
const float SS_SHOOT_TIME_HI = 2.75f;

// Bat animation
const int BAT_FRAMES = 10;
const float BAT_FRAME_TIME = 0.07f;
const int BAT_IMG_SIZE = 64;

const float BAT_HEALTH = 5.0f;
const float WB_TRIGGER_DIST = 38.0f;
const float DB_TRIGGER_DIST = 128.0f;
const float BAT_DAMAGE = 3.0f;

// Directions
const float D_RIGHT = 1.0f;
const float D_LEFT = -1.0f;

const float BAT_SPEED = 325.0f;

#endif