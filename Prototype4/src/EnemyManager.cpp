//==========================//
// EnemyManager.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "EnemyManager.h"
#include "EventManager.h"
#include "Laser.h"
#include "Player.h"

//==============================================================================
// EMScrollHandler::handleEvent(Event::Data)
// Handles Event::SCROLL by calling EnemyManager::scroll() through its internal
// EnemyManager pointer.
//==============================================================================
void EMScrollHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SCROLL)
		pEM->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}


void EMSpawnHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::SPAWN_ENEMY)
		pEM->spawn(sf::Vector2f(e.posX, e.posY), e.tile, e.dir);
}


void EMEDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH)
		pEM->startDeathAnim(e.posX, e.posY);
}

void EMTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pEM->clear();
}


// Constructor
EnemyManager::EnemyManager()
{

}
	// Destructor
EnemyManager::~EnemyManager()
{

}


void EnemyManager::startDeathAnim(float x, float y)
{
	deathAnim = true;
	timer = 0.0f;
	frame = 0;
	death.setPosition(x, y);
	death.setTextureRect(sf::IntRect(0,0,128,128));
}

void EnemyManager::init(sf::Texture *et, sf::Texture *dt)
{
	enemies = new Enemy[10];
	for (int i = 0; i < 10; i++)
	{
		enemies[i].setTexture(et);
		enemies[i].init();
	}
	index = 0;

	death.setTexture(*dt);
	deathAnim = false;
	death.setTextureRect(sf::IntRect(0,0,128,128));
	death.setOrigin(64.0f, 64.0f);

	scrollHandler = new EMScrollHandler(this);
	spawnHandler = new EMSpawnHandler(this);
	deathHandler = new EMEDeathHandler(this);
	transitionHandler = new EMTransitionHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::SPAWN_ENEMY, spawnHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, deathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);
}
	
void EnemyManager::spawn(sf::Vector2f pos, sf::Vector2i tile, float dir)
{
	enemies[index].activate(pos, tile, dir);
	index++;
}

void EnemyManager::scroll(sf::Vector2f ds)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].scroll(ds);
	if (deathAnim)
		death.move(-1.0f * ds);
}

bool EnemyManager::checkCollisions(Laser *laser)
{
	int i = 0;
	while (enemies[i].isActive())
	{
		if (enemies[i].collidesWith((Entity*)laser))
		{
			// Enemy::damage() returns true if enemy is killed
			if (enemies[i].damage(laser->getDamage()))
			{
				Event::Data e;
				e.type = Event::ENEMY_DEATH;
				e.tile = enemies[i].getSpawnTile();
				e.posX = enemies[i].getPosition().x;
				e.posY = enemies[i].getPosition().y;
				EventManager::triggerEvent(e);

				remove(i);

			}
            return true;
		}
		i++;
	}
    return false;
}

//==============================================================================
// EnemyManager::checkCollisions(Player*)
// Checks for collisions between active enemies and the player.  If a collision
// is detected, a PLAYER_HIT event is generated.
//==============================================================================
void EnemyManager::checkCollisions(Player *player)
{
	Event::Data e;
	e.type = Event::PLAYER_HIT;

	int i = 0;
	while (enemies[i].isActive())
	{
		if (enemies[i].getHitbox().intersects(player->getHitBox()))
		{
			e.damage = 5;
			EventManager::triggerEvent(e);
			return;
		}
		i++;
	}
}

void EnemyManager::update(float dt)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].update(dt);

	if (deathAnim)
	{
		timer += dt;

		if (timer > 0.125f)
		{
			timer = 0.0f;
			if (frame == 4)
				deathAnim = false;
			else
			{
				frame++;
				sf::IntRect rect(0,0,128,128);
				rect.left = frame * 128;
				death.setTextureRect(rect);
			}
		}
	}

}

void EnemyManager::draw(sf::RenderWindow& window)
{
	int i = 0;
	while (enemies[i].isActive())
		enemies[i++].draw(window);

	if (deathAnim)
		window.draw(death);
}

void EnemyManager::clear()
{
	Event::Data e;
	e.type = Event::DESPAWN_ENEMY;


	for (int i = 0; i < index; i++)
	{
		enemies[i].deactivate();
		e.tile = enemies[i].getSpawnTile();
		EventManager::triggerEvent(e);
	}
	index = 0;
}


void EnemyManager::remove(int ind)
{
    enemies[ind].deactivate();
    int j = 0;
    int k = 9;

    // Maintain "sorted" order, i.e. all active lasers are before inactive ones
    while (j < k)
	{
        while (enemies[j].isActive() && j < 9)
            j++;
        while (!enemies[k].isActive() && k > 0)
            k--;
        if (j < k)
		{
            enemies[j].copy(enemies[k]);
            enemies[k].deactivate();
		}
	}
    index--;
}