#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
public:
    virtual void update(float deltaTime) {};
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2f getPosition() const = 0;

};


