#include <SFML/Graphics.hpp>
#include <cmath>
#include "map.h"
#include <iostream>
#include <array>
#include "player.h"
#include "renderWindowSingleton.h"
#include "grid.h"



int main()
{
    // Create the window
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();




    Map map = Map();





    Grid grid = Grid();

    grid.mapToGrid(map);
    
    Player player = Player(map.getMainTile());


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Q ||
                    event.key.code == sf::Keyboard::E ||
                    event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::S ||
                    event.key.code == sf::Keyboard::D) {
                    player.move();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
                map.flag();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                map.update();
                grid.mapToGrid(map);
                player.changePlacement();
            
            }
                

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
                    map.setMapStrategy(2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert))
                    map.setMapStrategy(1);
            }
        }

        //player.move();

        window.clear(sf::Color::Black);

        
        map.drawMap();
        //player.drawPlayer();
        player.draw();



        window.display();
    }

    return 0;
}

