//==========================//
// PlayState.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "PlayState.h"
#include "Game.h"
#include "EventManager.h"
#include "Constants.h"
#include <fstream>
const float PlayState::GAME_OVER_DELAY = 1.0f;

void PSPickupHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_PICKUP)
		pPS->pushMessage(e.pickupType);
}

void PSPDeathAnimDoneHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::PLAYER_DEATH_ANIM_DONE)
		pPS->setGameOver(true);
}

void PSContinueHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::CONTINUE)
		pPS->setGameOver(false);
}

//================================
// Constructor
//================================
PlayState::PlayState(Game *game):
	GameState(game)
{
	pickupHandler = NULL;
	continueHandler = NULL;
	deathAnimDoneHandler = NULL;
}

//==============================
// Destructor
//==============================
PlayState::~PlayState()
{
	if (deathAnimDoneHandler)
		delete deathAnimDoneHandler;
	if (continueHandler)
		delete continueHandler;
	if (pickupHandler)
		delete pickupHandler;
}

// Methods
bool PlayState::init()
{
	//tmap.setTexture(pGame->getTexture(TILES));
	//tmap.loadFromFile("map2.txt");
	//tmap.init();

	//player.setTexture(pGame->getTexture(PLAYER));
	//player.init();

	blackhole.setTexture(pGame->getTexture(BLACK_HOLE));
	blackhole.init();
	//blackhole.activate(sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));

	deathAnimator.init(pGame->getTexture(DEATH));

	enemies.init(pGame->getTexture(ENEMY), pGame->getTexture(BAT), pGame->getTexture(CRAWLER));
	eProjectiles.init(pGame->getTexture(SPIT));

	barriers.init(pGame->getTexture(ICE));

	pickups.init(pGame->getTexture(HP), pGame->getTexture(GRAVITY), pGame->getTexture(ENERGY));

	world.loadFromFile("world.txt", pGame);
	world.init();

	player.setTexture(pGame->getTexture(PLAYER));
	player.init();
	player.setTileMap(world.getActiveMap());

	//pickups.init(pGame->getTexture(HP), pGame->getTexture(GRAVITY), pGame->getTexture(ENERGY));

    pProjectiles.init(pGame->getTexture(LASER), pGame->getTexture(FREEZE), pGame->getTexture(FLAME), pGame->getTexture(GRAVITY));
	player.setEnemyManager(&enemies);
	player.setBarrierManager(&barriers);
    //player.setProjectiles(&pProjectiles);

	hud.init(pGame->getTexture(HBAR), pGame->getTexture(ENERGY), pGame->getTexture(GRAVITY));


	pickupHandler = new PSPickupHandler(this);
	continueHandler = new PSContinueHandler(this);
	deathAnimDoneHandler = new PSPDeathAnimDoneHandler(this);

	EventManager::addHandler(Event::PLAYER_PICKUP, pickupHandler);
	EventManager::addHandler(Event::PLAYER_DEATH_ANIM_DONE, deathAnimDoneHandler);
	EventManager::addHandler(Event::CONTINUE, continueHandler);

	//background.setTexture(*(pGame->getTexture(BKGD)));
	//float scale = SCREEN_HEIGHT / background.getLocalBounds().height;
	//background.setScale(scale, scale);

	world.transition(START_ENTRANCE);
	gameOver = false;

	return true;
}

void PlayState::setGameOver(bool go)
{
	gameOver = go;
	timer = 0.0f;
}

void PlayState::handleInput(Input *input)
{
	player.handleInput(*input);
}

void PlayState::pushMessage(int type)
{
	switch (type)
	{
	case P_FLAMETHROWER:
		pGame->requestStateChange(GSCR_PUSH_MSG_FLAME);
		break;
	case P_FREEZERAY:
		pGame->requestStateChange(GSCR_PUSH_MSG_FREEZE);
		break;
	default:
		break;
	}
}

void PlayState::update(float dt)
{
	//if (blackhole.isActive())
		//blackhole.update(dt);
	if (gameOver)
	{
		timer += dt;

		if (timer > GAME_OVER_DELAY)
			pGame->requestStateChange(GSCR_PUSH_GAMEOVER);
	}


	player.update(dt);
	//tmap.update(dt);
	world.update(dt);
	enemies.setPlayerPosition(player.getPosition());
	enemies.update(dt);
    pProjectiles.update(dt);
	eProjectiles.update(dt);
	pickups.update(dt);
	deathAnimator.update(dt);
	barriers.update(dt);

	pProjectiles.checkCollisions(&enemies);
	pProjectiles.checkCollisions(&barriers);
	if (blackhole.isActive())
		enemies.checkCollisions(&blackhole);
	pickups.checkCollisions(&player);

	if (!player.isDamaged())
		eProjectiles.checkCollisions(&player);

	if (!player.isDamaged())
		enemies.checkCollisions(&player);

	if (blackhole.isActive())
		blackhole.update(dt);
}

void PlayState::draw(sf::RenderWindow& window)
{
	//int bkgdRepeat = (int)(SCREEN_WIDTH / background.getGlobalBounds().width) + 1;
	//sf::Vector2f pos = background.getPosition();
	//for (int i = 0; i < bkgdRepeat; i++)
	//{
		//pos.x = i * background.getGlobalBounds().width;
		//background.setPosition(pos);
		//window.draw(background);
	//}
	//background.setPosition(0.0f, 0.0f);

	//tmap.draw(window);
	world.draw(window);
	barriers.draw(window);
	if (blackhole.isActive())
		blackhole.draw(window);
	//eProjectiles.draw(window);
	//pProjectiles.draw(window);
	enemies.draw(window);
	pProjectiles.draw(window);
	eProjectiles.draw(window);
	player.draw(window);
	pickups.draw(window);
	deathAnimator.draw(window);
	hud.draw(window);
}