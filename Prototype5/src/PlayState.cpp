//==========================//
// PlayState.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "PlayState.h"
#include "Game.h"

//================================
// Constructor
//================================
PlayState::PlayState(Game *game):
	GameState(game),
	healthbar(Health::MAX_HEALTH, Health::MAX_HEALTH)
{

}

//==============================
// Destructor
//==============================
PlayState::~PlayState()
{

}

// Methods
bool PlayState::init()
{
	//tmap.setTexture(pGame->getTexture(TILES));
	//tmap.loadFromFile("map2.txt");
	//tmap.init();

	//player.setTexture(pGame->getTexture(PLAYER));
	//player.init();

	enemies.init(pGame->getTexture(ENEMY), pGame->getTexture(DEATH));
	eProjectiles.init(pGame->getTexture(SPIT));

	world.loadFromFile("world.txt", pGame);
	world.init();

	player.setTexture(pGame->getTexture(PLAYER));
	player.init();
	player.setTileMap(world.getActiveMap());
	enemies.setTileMap(world.getActiveMap());

	pickups.init(pGame->getTexture(HP));

    pProjectiles.init(pGame->getTexture(LASER), pGame->getTexture(FREEZE), pGame->getTexture(FLAME));
	player.setEnemyManager(&enemies);
    //player.setProjectiles(&pProjectiles);

	healthbar.setTexture(pGame->getTexture(HBAR));
	healthbar.init();


	background.setTexture(*(pGame->getTexture(BKGD)));
	float scale = SCREEN_HEIGHT / background.getLocalBounds().height;
	background.setScale(scale, scale);



	return true;
}

void PlayState::handleInput(Input *input)
{
	player.handleInput(*input);
}

void PlayState::update(float dt)
{
	player.update(dt);
	//tmap.update(dt);
	world.update(dt);
	enemies.setPlayerPosition(player.getPosition());
	enemies.update(dt);
    pProjectiles.update(dt);
	eProjectiles.update(dt);
	pickups.update(dt);

	pProjectiles.checkCollisions(&enemies);

	pickups.checkCollisions(&player);

	if (!player.isDamaged())
		eProjectiles.checkCollisions(&player);

	if (!player.isDamaged())
		enemies.checkCollisions(&player);
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
	//eProjectiles.draw(window);
	//pProjectiles.draw(window);
	enemies.draw(window);
	pProjectiles.draw(window);
	eProjectiles.draw(window);
	player.draw(window);
	pickups.draw(window);
	healthbar.draw(window);
}