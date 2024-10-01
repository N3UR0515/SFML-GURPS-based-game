#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include "map.h"
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <thread>
#include <vector>
#include <memory>
#include <map>
#include "character.h"
#include "renderWindowSingleton.h"
#include "grid.h"
#include "skillList.h"
#include "tempSide.h"


void handleClient(std::shared_ptr<sf::TcpSocket> clientSocket, Character* player, std::vector<std::shared_ptr<sf::TcpSocket>> &clients, std::vector<Character>& players, int playerCount)
{
    char buffer[2000];
    std::size_t received;
    tempSide s;
    player->serverSideDirectionStrategy(&s);
    while (true)
    {
        sf::Socket::Status status = clientSocket->receive(buffer, sizeof(buffer), received);
        if (status == sf::Socket::Done)
        {
            std::cout << "Client " << player->id << " says: " << buffer << std::endl;
            int direction = 0;
            int type = 0; // type 0 - movement, type 1 - attack
            std::istringstream iss(buffer);
            iss >> direction >> type;
            s.setSide(direction);
            std::string message = "1 " + std::to_string(player->id) + " " + std::to_string(direction);
            switch (type)
            {
            case 0:
                player->move();
                for (auto& c : clients)
                {
                    if (c != clientSocket)
                        if (c->send(message.c_str(), message.size() + 1) != sf::Socket::Done)
                        {
                            std::cerr << "Err" << std::endl;
                        }
                }
                break;
            case 1:
                player->attack(players);
                players.erase(
                    std::remove_if(players.begin(), players.end(),
                        [&playerCount, &clients, &player](const Character& c) {
                            if (c.personalSkills.at("HP") <= 0)
                            {
                                std::string message = "2 " + std::to_string(c.id) + " " + std::to_string(-1);
                                for (auto& c : clients)
                                {
                                    if (c->send(message.c_str(), message.size() + 1) != sf::Socket::Done)
                                    {
                                        std::cerr << "Err" << std::endl;
                                    }
                                }
                                playerCount--;
                                return true;
                            }
                            return false;
                        }),
                    players.end());
                break;
            }
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cerr << "Client disconnected" << std::endl;
            break;
        }
        else if (status == sf::Socket::Error)
        {
            std::cerr << "Socket Error" << std::endl;
            break;
        }
    }
    
}

int main()
{
    std::cout << "HOSTING?" << std::endl;
    bool host;
    std::cin >> host;

    if (host)
    {
        sf::TcpListener listener;
        if (listener.listen(53000) != sf::Socket::Done)
        {
            return 1;
        }
        std::cout << "Server is listening on port 53000" << std::endl;
        listener.setBlocking(false);

        std::vector<std::shared_ptr<sf::TcpSocket>> clients;
        std::vector<std::thread> clientThreads;

        std::vector<Character> players;


        Map map = Map(); // Initialize the connections between tiles
        map.loadMap();
        Grid grid = Grid(); // Setting up the starting and the distances of the grid

        Map map2 = Map();
        map2.loadMap();

        map.getMainTile()->presetReveal(map2.getMainTile(), 0);

        grid.mapToGrid(map.getMainTile());


        int playerCount = 0;
        //Character player = Character(map.getMainTile());

        players.push_back(Character(map.getMainTile(), 1));
        players.push_back(Character(map.getMainTile(), 2));
        players.push_back(Character(map.getMainTile(), 3));
        players.push_back(Character(map.getMainTile(), 4));



        // Create the window using Singleton pattern
        sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();

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

                        //player.changePlacement();

                        grid.mapToGrid(map.getMainTile());
                        map.flag();
                        map.update1();
                        for (Character& p : players)
                        {
                            if (playerCount > p.id - 1)
                            {
                                p.changePlacement();
                            }
                            
                        }

                        std::string message = map.constructPacket();
                        for (auto& client : clients)
                        {
                            if (client->send(message.c_str(), message.size() + 1) != sf::Socket::Done)
                            {
                                std::cerr << "Err" << std::endl;
                            }
                        }
                        

                    }

                    if (event.key.code == sf::Keyboard::B)
                    {
                        map.saveMap();
                    }
                    if (event.key.code == sf::Keyboard::L)
                    {
                        map.loadMap();
                        grid.mapToGrid(map.getMainTile());
                        //player.moveOntoTile(map.getMainTile());
                        //player.changePlacement();
                    }
                    if (event.key.code == sf::Keyboard::K)
                    {
                        map.deleteMap(map.getMainTile());
                    }
                    if (event.key.code == sf::Keyboard::R)
                    {
                        map.getMainTile()->reveal();
                        grid.mapToGrid(map.getMainTile());
                    }
                }

                /*if (event.type == sf::Event::MouseButtonPressed)
                    map.flag();

               /* if (event.type == sf::Event::MouseButtonReleased)
                {
                    map.update(player);
                    grid.mapToGrid(map);
                    player.changePlacement();

                }*/


                if (event.type == sf::Event::KeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
                    {
                        map.setMapStrategy(3);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) || sf::Keyboard::isKeyPressed(sf::Keyboard::Insert) || sf::Keyboard::isKeyPressed(sf::Keyboard::End))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
                            map.setMapStrategy(2);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert))
                            map.setMapStrategy(1);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
                            map.setMapStrategy(4);
                        //createMode = true;
                    }


                }
            }



            try {
                auto client = std::make_shared<sf::TcpSocket>();
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "New Client Connected!" << std::endl;
                    client->setBlocking(false);
                    clients.push_back(client);
                    
                    clientThreads.emplace_back(handleClient, client, &players.at(playerCount), ref(clients), ref(players), playerCount);
                    playerCount++;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Exception " << e.what() << std::endl;
            }
            

            window.clear(sf::Color::Black);

            map.drawMap();

            for (Character& p : players)
            {
                if (playerCount > p.id - 1)
                    p.draw();
            }

            window.display();


        }

        for (auto& thread : clientThreads)
        {
            if (thread.joinable())
                thread.join();
        }
    }
    else
    {
        sf::TcpSocket socket;
        std::string serverAddress;
        std::cout << "Enter the server IP address: ";
        std::cin >> serverAddress;

        if (socket.connect(serverAddress, 53000) != sf::Socket::Done)
        {
            return 1;
        }
        std::cout << "Connected to the server!" << std::endl;

        Map map = Map(); // Initialize the connections between tiles
        map.loadMap();
        tempSide sider = tempSide();
        map.clientSideDirectionStraregy(&sider);
        Grid grid = Grid(); // Setting up the starting and the distances of the grid
        Character player = Character(map.getMainTile(), 0);

        std::vector<Character> players;
        players.push_back(Character(map.getMainTile(), 1));
        players.push_back(Character(map.getMainTile(), 2));
        players.push_back(Character(map.getMainTile(), 3));

        std::vector<tempSide*> helpers;
        helpers.push_back(new tempSide());
        helpers.push_back(new tempSide());
        helpers.push_back(new tempSide());

        for (int i = 0; i < 3; i++)
        {
            players.at(i).serverSideDirectionStrategy(helpers.at(i));
        }
        int playerCount = 0;

        std::map<int, int> playerIds;

        grid.mapToGrid(player.getTile());
        bool dead = false;

        std::thread serverThread([&socket, &map, &sider, &playerIds, &players, &helpers, &dead]()
            {
                char buffer[2000];
                std::size_t received;
                while (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
                {
                    int type;
                    int strat;
                    int side;

                    std::cout << "2PAC: " << buffer << std::endl;
                    std::istringstream iss(buffer);
                    try {
                        iss >> type >> strat >> side;

                        switch (type)
                        {
                        case 0:
                            std::cout << "PACKET:" << strat << "  " << side << std::endl;
                            map.setMapStrategy(strat);
                            sider.setSide(side);
                            map.flag();
                            map.update1();
                            break;
                        case 1:
                            std::cout << "FROM ANOTHER PLAYER: " << strat << "  " << side << std::endl;
                            switch (playerIds.find(strat) != playerIds.end())
                            {
                            case false:
                                playerIds[strat] = playerIds.size();
                            case true:
                                helpers.at(playerIds[strat])->setSide(side);
                                players.at(playerIds[strat]).move();
                                break;
                            }
                            break;
                        case 2:
                            switch (playerIds.find(strat) != playerIds.end())
                            {
                            case false:
                                std::cout << "YOU HAVE DIED" << std::endl;
                                dead = true;
                                break;
                            case true:
                                for (const auto& pair : playerIds)
                                {
                                    std::cout << pair.first << " " << pair.second << std::endl;
                                    std::cout << strat << std::endl;
                                }
                                auto it = playerIds.find(strat);
                                //players.erase(players.begin() + playerIds[strat]);
                                playerIds.erase(it);
                                break;
                            }
                        default:
                            break;
                        }

                        
                    }
                    catch (const std::exception& e) {
                        std::cout << "PAC: " << buffer << std::endl;
                    }  
                    
                }
            });

        

        //map.saveMap();


        sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();

        while (window.isOpen())
        {
            sf::Event event;
            if (dead)
                window.close();

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

                        //player.changePlacement();

                        

                        grid.mapToGrid(player.getTile());
                        player.move();
                        for (Character& c : players)
                        {
                            c.changePlacement();
                        }
                        std::string message = std::to_string(player.getLastSide()) + " 0";
                        if (socket.send(message.c_str(), message.size() + 1) != sf::Socket::Done)
                        {
                            std::cerr << "Err" << std::endl;
                        }
                    }

                    if (event.key.code == sf::Keyboard::B)
                    {
                        player.attack(players);
                        std::string message = std::to_string(player.getLastSide()) + " 1";
                        if (socket.send(message.c_str(), message.size() + 1) != sf::Socket::Done)
                        {
                            std::cerr << "Err" << std::endl;
                        }
                    }
                }
            }


            window.clear(sf::Color::Black);

            player.drawPlayer();

            for (const auto& pair : playerIds)
            {
                players.at(pair.second).draw();
            }
            window.display();

            
        }
        serverThread.join();

    }

    return 0;
}

