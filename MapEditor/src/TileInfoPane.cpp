//==========================//
// TileInfoPane.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "TileInfoPane.h"
#include <sstream>

TileInfoPane::TileInfoPane(const sf::Font& f):
	font(f),
	tileType(f, 5),
	scrollXBarrier(f, 2),
	scrollYBarrier(f, 2),
	enemySpawn(f, 5),
	top(f, "Top", 16, 5),
	left(f, "Left", 16, 5),
	width(f, "Width", 16, 5),
	height(f, "Height", 16, 5),
	bounds(800.0f, 0.0f, 200.0f, 675.0f),
	background(sf::Vector2f(200.0f, 675.0f))
{
	background.setFillColor(sf::Color(225, 225, 225));
	background.setOutlineThickness(1);
	background.setOutlineColor(sf::Color::Black);
	background.setPosition(801.0f, 0.0f);
}

TileInfoPane::~TileInfoPane()
{
}

void TileInfoPane::init()
{
	// Initialize tileIndex text
	tileIndex.setFont(font);
	tileIndex.setString("Tile (,)");
	tileIndex.setColor(sf::Color::Black);
	tileIndex.setCharacterSize(20);
	sf::FloatRect bounds = tileIndex.getLocalBounds();
	tileIndex.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	tileIndex.setPosition(900.0f, 20.0f);

	// Initialize the tileType radiobutton
	tileType.init();
	tileType.setSelected(0);
	tileType.setTitle(std::string("Tile Type"), 18);
	tileType.setOption(std::string("Background"), 16, TileNS::BACKGROUND);
	tileType.setOption(std::string("Floor"), 16, TileNS::FLOOR);
	tileType.setOption(std::string("Wall"), 16, TileNS::WALL);
	tileType.setOption(std::string("Ladder"), 16, TileNS::LADDER);
	tileType.setOption(std::string("Ladder Top"), 16, TileNS::LADDER_TOP);
	tileType.setPosition(sf::Vector2f(815.0f, 35.0f));

	// Initialize hitbox text
	hitbox.setFont(font);
	hitbox.setString("Tile Hitbox");
	hitbox.setCharacterSize(18);
	hitbox.setColor(sf::Color::Black);
	bounds = hitbox.getLocalBounds();
	//hitbox.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	hitbox.setPosition(815.0f, 175.0f);

	// Initialize the top field
	top.setPosition(sf::Vector2f(835.0f, 205.0f));
	top.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the left field
	left.setPosition(sf::Vector2f(835.0f, 235.0f));
	left.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the width field
	width.setPosition(sf::Vector2f(820.0f, 265.0f));
	width.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the height field
	height.setPosition(sf::Vector2f(815.0f, 295.0f));
	height.setTextAreaOutline(2, sf::Color::Black);

	// Initialize the scrollXbarrier radiobutton
	scrollXBarrier.init();
	scrollXBarrier.setSelected(0);
	scrollXBarrier.setTitle(std::string("ScrollX Barrier"), 18);
	scrollXBarrier.setOption(std::string("No"), 16, 0);
	scrollXBarrier.setOption(std::string("Yes"), 16, 1);
	scrollXBarrier.setPosition(sf::Vector2f(815.0f, 320.0f));

	// Initialize the scrollYbarrier radiobutton
	scrollYBarrier.init();
	scrollYBarrier.setSelected(0);
	scrollYBarrier.setTitle(std::string("ScrollY Barrier"), 18);
	scrollYBarrier.setOption(std::string("No"), 16, 0);
	scrollYBarrier.setOption(std::string("Yes"), 16, 1);
	scrollYBarrier.setPosition(sf::Vector2f(815.0f, 400.0f));

	// Initialize the scrollYbarrier radiobutton
	enemySpawn.init();
	enemySpawn.setSelected(0);
	enemySpawn.setTitle(std::string("Spawn Enemy"), 18);
	enemySpawn.setOption(std::string("None"), 16, 0);
	enemySpawn.setOption(std::string("Soldier"), 16, 1);
	enemySpawn.setOption(std::string("Grenadier"), 16, 2);
	enemySpawn.setOption(std::string("Super Soldier"), 16, 3);
	enemySpawn.setOption(std::string("Turret"), 16, 4);
	enemySpawn.setPosition(sf::Vector2f(815.0f, 470.0f));

	// Initialize the apply button
	sf::Vector2f size;
	size.x = 80.0f;
	size.y = 35.0f;
	std::string str = "Apply";
	apply.setSize(size);
	apply.setText(font, str, 15);
	apply.setTextColors(sf::Color::Black, sf::Color(210, 210, 210));
	apply.setButtonColors(sf::Color(160, 160, 160), sf::Color(160, 160, 160), sf::Color(130,130,130), sf::Color(130,130,130));
	apply.setOutline(1, sf::Color::Black);
	apply.setActive(true);
	apply.setPosition(sf::Vector2f(870.0f, 620.0f));
}

void TileInfoPane::getTileInfo(Tile *t, sf::Vector2i index)
{
	tile = t;
	if (tile == NULL)
		return;

	std::stringstream ss;

	// Update the tile index text
	ss << "Tile (" << index.x << ", " << index.y << ")";
	tileIndex.setString(ss.str());
	sf::FloatRect bounds = tileIndex.getLocalBounds();
	tileIndex.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	tileIndex.setPosition(900.0f, 20.0f);

	// Set the selected tile type radio button
	tileType.setSelected((int)tile->type);

	// Set the hitbox left text field
	ss.str("");
	ss << tile->hitbox.left;
	left.setEnteredText(ss.str());

	// Set the hitbox top text field
	ss.str("");
	ss << tile->hitbox.top;
	top.setEnteredText(ss.str());

	// Set the hitbox width text field
	ss.str("");
	ss << tile->hitbox.width;
	width.setEnteredText(ss.str());

	// Set the hitbox height text field
	ss.str("");
	ss << tile->hitbox.height;
	height.setEnteredText(ss.str());

	scrollXBarrier.setSelected(tile->scrollXBarrier ? 1 : 0);
	scrollYBarrier.setSelected(tile->scrollYBarrier ? 1 : 0);

	enemySpawn.setSelected(tile->enemy);
}


void TileInfoPane::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();

	if (bounds.contains(mousePos))
	{
		tileType.handleInput(input);
		scrollXBarrier.handleInput(input);
		scrollYBarrier.handleInput(input);
		enemySpawn.handleInput(input);
		top.handleInput(input);
		left.handleInput(input);
		width.handleInput(input);
		height.handleInput(input);
		apply.handleInput(input);
	}
}

void TileInfoPane::update(float dt)
{
	tileType.update(dt);
	scrollXBarrier.update(dt);
	scrollYBarrier.update(dt);
	enemySpawn.update(dt);

	if (apply.wasClicked())
	{
		tile->type = (TileNS::Type)tileType.getSelected();
		tile->hitbox.left = (float)atof(left.getEnteredText().c_str());
		tile->hitbox.top = (float)atof(top.getEnteredText().c_str());
		tile->hitbox.width = (float)atof(width.getEnteredText().c_str());
		tile->hitbox.height = (float)atof(height.getEnteredText().c_str());
		tile->scrollXBarrier = scrollXBarrier.getSelected() == 0 ? false : true;
		tile->scrollYBarrier = scrollYBarrier.getSelected() == 0 ? false : true;
		tile->enemy = enemySpawn.getSelected();
	}

}

void TileInfoPane::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(tileIndex);
	tileType.draw(window);
	window.draw(hitbox);
	top.draw(window);
	left.draw(window);
	width.draw(window);
	height.draw(window);
	scrollXBarrier.draw(window);
	scrollYBarrier.draw(window);
	enemySpawn.draw(window);
	apply.draw(window);
}