#pragma once
#include <SFML/Graphics.hpp>
#include"Entity.h"
#include <iostream>
#include <ctime>        // for srand and time

using namespace std;
using namespace sf;

class Enemy : public Entity
{
private:
    Sprite sprite;
    Vector2f position;
    Texture texture;
    bool alive; // Draws enemy if it is alive

public:
    Enemy():alive(true)
    {
        // Seed the random number generator
        srand((time(0)));

        // Load texture
        if (!texture.loadFromFile("./images/enemy.png"))
        {
            cout << "\nFailed to load enemy texture!" << endl;
        }
		Vector2f playerPosition(20,20);

        sprite.setTexture(texture);

    }
    void generateRandomPosition(const Vector2f& playerPosition, Enemy* enemies[], int numEnemies)
    {
        int screenWidth = 600;
        int screenHeight = 600;
        int blockSize = 20;
        int x, y;
        bool positionValid;
        Vector2f newPos;
        do
        {
            positionValid = true;
            x = (rand() % (screenWidth / blockSize)) * blockSize;
            y = (rand() % (screenHeight / blockSize)) * blockSize;

            // Re-generate x if it is first column or last column
            while (x == 0 || x == screenWidth - blockSize)
            {
                x = (rand() % (screenWidth / blockSize)) * blockSize;
            }

            // Re-generate y 
            while (y == 0 || y == screenHeight - blockSize)
            {
                y = (rand() % (screenHeight / blockSize)) * blockSize;
            }

            newPos.x = x;
            newPos.y = y;

            // Ensure the new position does not overlap with the player
            if (playerPosition == newPos)
            {
                positionValid = false;
            }

            // Checking other enemy positions
            for (int i = 0; i < numEnemies; ++i)
            {
                if (enemies[i] != nullptr && enemies[i] != this)
                {
                    if (enemies[i]->getPosition() == newPos)
                    {
                        positionValid = false;
                        break;
                    }
                }
            }
        } while (!positionValid);

        position = newPos;
        sprite.setPosition(position);
    }


    void update(float deltaTime) override{}

    void draw(RenderWindow& window) override
    {
        if (alive) // Only draw if the enemy is alive
        {
            window.draw(sprite);
        }
    }

    void setPosition(float x, float y) override
    {
        position = Vector2f(x, y);
        sprite.setPosition(position);
    }

    Vector2f getPosition() const override
    {
        return this->position;
    }

    bool isAlive() const
    {
        return this->alive;
    }

    void kill()
    {
        this->alive = false; // Set the enemy's status to dead
    }
};
