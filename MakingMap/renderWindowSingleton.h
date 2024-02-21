#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class RenderWindowSingleton
{
protected:
    RenderWindowSingleton()
        : window_(sf::VideoMode(800, 600), "Áveskite pavadinimà 3")
    {
    }

    static RenderWindowSingleton* instance_;

    sf::RenderWindow window_;

public:
    RenderWindowSingleton(RenderWindowSingleton& other) = delete;
    void operator=(const RenderWindowSingleton&) = delete;

    static RenderWindowSingleton* GetInstance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new RenderWindowSingleton();
        }
        return instance_;
    };

    sf::RenderWindow& getWindow()
    {
        return window_;
    }
};