//==========================//
// PlayerProjectiles.cpp    //
// Author: Matthew Stephens //
//==========================//
#include "PlayerProjectiles.h"
#include "Laser.h"
#include "EnemyManager.h"
#include "EventManager.h"
#include "Constants.h"


// PPScrollHandler Constructor
PPScrollHandler::PPScrollHandler(PlayerProjectiles *pp)
{
	pPP = pp;
}
	
void PPScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pPP->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}


// PPShootHandler Constructor
PPShootHandler::PPShootHandler(PlayerProjectiles *pp)
{
	pPP = pp;
}
	
void PPShootHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_SHOOT)
		pPP->spawn(sf::Vector2f(e.posX, e.posY), e.dir);
}



// Constructor
PlayerProjectiles::PlayerProjectiles()
{


}
// Destructor
PlayerProjectiles::~PlayerProjectiles()
{
	if (scrollHandler)
		delete scrollHandler;
}

void PlayerProjectiles::init(sf::Texture *t)
{
	lasers = new Laser[10];
	for (int i = 0; i < 10; i++)
	{
		lasers[i].setTexture(t);
		lasers[i].init();
	}
	index = 0;

	// Register event handlers
	scrollHandler = new PPScrollHandler(this);
	shootHandler = new PPShootHandler(this);

	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::PLAYER_SHOOT, shootHandler);
}
	
void PlayerProjectiles::spawn(sf::Vector2f pos, float dir)
{
	if (index == 10)
		return;
	lasers[index].activate(pos, dir);
	index++;
}

void PlayerProjectiles::checkCollisions(EnemyManager *enemies)
{
	int i = 0;
	while (lasers[i].isActive() && i < 10)
		if (enemies->checkCollisions(&lasers[i]))
            remove(i);
		else
            i++;
}

void PlayerProjectiles::scroll(sf::Vector2f ds)
{
	int i = 0;
	while (lasers[i].isActive() && i < 10)
		lasers[i++].scroll(ds);
}

void PlayerProjectiles::update(float dt)
{
	int i = 0;
	while (lasers[i].isActive() && i < 10)
	{
		float dir = lasers[i].getDir();
		lasers[i].move(sf::Vector2f(dir * lasers[i].getSpeed() * dt, 0.0f));

        // If laser is offscreen, deactivate it
        bool offScreenRight = lasers[i].getPosition().x > SCREEN_WIDTH;
        bool offScreenLeft = lasers[i].getPosition().x < 0.0f - lasers[i].getHitbox().width;
        if (offScreenRight || offScreenLeft)
            remove(i);
		else
            i++;
	}

    // 
}

void PlayerProjectiles::draw(sf::RenderWindow& window)
{
	int i = 0;
	while (lasers[i].isActive())
		lasers[i++].draw(window);
}

void PlayerProjectiles::remove(int ind)
{
    lasers[ind].deactivate();
    int j = 0;
    int k = 9;

    // Maintain "sorted" order, i.e. all active lasers are before inactive ones
    while (j < k)
	{
        while (lasers[j].isActive() && j < 9)
            j++;
        while (!lasers[k].isActive() && k > 0)
            k--;
        if (j < k)
		{
            lasers[j].copy(lasers[k]);
            lasers[k].deactivate();
		}
	}
    index--;
}