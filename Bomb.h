#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class Bomb
{
private:
    Vector2f position;
    Texture bombTexture;
    Sprite bombSprite;
    Clock timer; 
    float explosionTime;  // Time after which the bomb explodes

public:
    Bomb(float x, float y) : explosionTime(2.0f) // Bomb explodes after 2 seconds
    {
        position = Vector2f(x, y);

        // Load the bomb texture
        if (!bombTexture.loadFromFile("./images/bomb.png"))
        {
            cout << "\nUnable to load bomb texture!" << endl;
        }

        bombSprite.setTexture(bombTexture);
        bombSprite.setPosition(position);
        timer.restart(); 
    }

    void draw(RenderWindow& window)
    {
        window.draw(bombSprite);
    }

    bool shouldExplode() const
    {
        return timer.getElapsedTime().asSeconds() >= explosionTime;
    }

    Vector2f getPosition() const
    {
        return position;
    }
};
