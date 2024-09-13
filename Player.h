#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bomb.h"
#include "Enemy.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const float GRID_WIDTH = 600.0f; // Grid width
const float GRID_HEIGHT = 600.0f; // Grid height

class Player : public Entity
{
private:
    enum Direction { Down, Left, Right, Up };
    int lives;
    int score;
    Bomb* bomb;
    float speed;
    Vector2f position;
    Sprite sprite;

    // Textures for each direction
    Texture downTexture;
    Texture upTexture;
    Texture leftTexture;
    Texture rightTexture;

    // File paths for each direction's image
    const string downSpritePath = "./images/playerDown.png";
    const string upSpritePath = "./images/playerUp.png";
    const string leftSpritePath = "./images/playerLeft.png";
    const string rightSpritePath = "./images/playerRight.png";

    void setDirection(Direction dir)
    {
        switch (dir)
        {
        case Down:
            sprite.setTexture(downTexture);
            break;
        case Left:
            sprite.setTexture(leftTexture);
            break;
        case Right:
            sprite.setTexture(rightTexture);
            break;
        case Up:
            sprite.setTexture(upTexture);
            break;
        }
    }

public:
    Player(float frameWidth, float frameHeight, float duration) : speed(100.0f), position(20, 20), lives(3), score(0), bomb(nullptr)
    {
        // Load textures for each direction
        if (!downTexture.loadFromFile(downSpritePath) || !upTexture.loadFromFile(upSpritePath) || !leftTexture.loadFromFile(leftSpritePath) || !rightTexture.loadFromFile(rightSpritePath))
        {
            cout << "\nUnable to Load Player Textures." << endl;
        }

        // Set initial texture
        sprite.setTexture(downTexture);
        sprite.setPosition(position);
    }

    ~Player()
    {
        if (bomb)
        {
            delete bomb;
        }
    }

    void update(float deltaTime, Enemy* enemies[], int enemyCount)
    {
        handleInput(deltaTime);

        // Check if the bomb should explode
        if (bomb && bomb->shouldExplode())
        {
            Vector2f bombPos = bomb->getPosition();

            for (int i = 0; i < enemyCount; ++i)
            {
                if (enemies[i] != nullptr)
                {
                    Vector2f enemyPos = enemies[i]->getPosition();

                    // checks if enemy is in range
                    bool inRange = (abs(bombPos.x - enemyPos.x) <= 60 && abs(bombPos.y - enemyPos.y) <= 60) ||
                        ((abs(bombPos.x - enemyPos.x) <= 3 * 20 && abs(bombPos.y - enemyPos.y) == 0) || 
                            (abs(bombPos.y - enemyPos.y) <= 3 * 20 && abs(bombPos.x - enemyPos.x) == 0));

                    if (inRange)
                    {
                        delete enemies[i];
                        enemies[i] = nullptr;
                        score += 20;
                    }
                }
            }

            delete bomb;
            bomb = nullptr;
           
        }
    }

    void handleInput(float deltaTime)
    {
        bool moved = false;
        Direction dir = Down;

        // Calculate new position based on input
        Vector2f newPosition = position;

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = Up;
            newPosition.y -= speed * deltaTime;
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = Down;
            newPosition.y += speed * deltaTime;
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = Left;
            newPosition.x -= speed * deltaTime;
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = Right;
            newPosition.x += speed * deltaTime;
            moved = true;
        }

        // movement within grid boundaries
        if (moved)
        {
            if (newPosition.x < 20)
            {
                newPosition.x = 20;
            }
            if (newPosition.x > GRID_WIDTH - 20 - sprite.getGlobalBounds().width) 
            {
                newPosition.x = GRID_WIDTH - 20 - sprite.getGlobalBounds().width;
            }
            if (newPosition.y < 20)
            {
                newPosition.y = 20;
            }
            if (newPosition.y > GRID_HEIGHT - 20 - sprite.getGlobalBounds().height)
            {
                newPosition.y = GRID_HEIGHT - 20 - sprite.getGlobalBounds().height;
            }

            // Update the position and direction
            position = newPosition;
            setDirection(dir);
            sprite.setPosition(position);
        }

        // Check if a bomb should be placed
        if (Keyboard::isKeyPressed(Keyboard::B) && bomb == nullptr)
        {
            bomb = new Bomb(position.x, position.y);
        }
    }


    void draw(RenderWindow& window) override
    {
        window.draw(sprite);
        if (bomb)
        {
            bomb->draw(window);
        }
    }

    void setPosition(float x, float y) override
    {
        position = Vector2f(x, y);
        sprite.setPosition(x, y);
    }

    Vector2f getPosition() const override
    {
        return position;
    }

    const Sprite& getSprite() const
    {
        return this->sprite;
    }

    int getLives() const
    {
        return this->lives;
    }

    void setLives(int newLives)
    {
        this->lives = newLives;
    }

    int getScore() const
    {
        return this->score;
    }

    void setScore(int newScore)
    {
        this->score = newScore;
    }
};
