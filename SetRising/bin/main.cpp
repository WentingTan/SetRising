#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TileMap.h"
#include "Player.h"

int main(int argc, char** argv)
{
  // create main window
	sf::RenderWindow window(sf::VideoMode(800,600,32), "Hello World - SFML");

	sf::Clock clock;
   TileMap tmap;
   tmap.init("map.txt");

   Player player;
   player.init();
   player.setTileMap(&tmap);

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		player.handleInput();
		player.update(dt.asSeconds());
		tmap.update(dt.asSeconds());
		window.clear();
		tmap.draw(window);
		player.draw(window);
		window.display();
	}

  // Done.
  return 0;
}
