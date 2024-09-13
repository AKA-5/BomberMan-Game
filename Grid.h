#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

const unsigned int GRID_SIZE = 30;

class Grid
{
    unsigned int blockSize = 20;
    Texture blockTexture; // Texture for block blocks
    Texture woodTexture;  // Texture for wood blocks
    Sprite blockSprite;   // Sprite to draw the block blocks
    Sprite woodSprite;    // Sprite to draw the wood blocks
    Sprite** blocks;      // Pointer to a 2D array of sprites

public:
    Grid();         // Constructor
    ~Grid();        // Destructor
    void initializeGrid();  // Grid initialization method
    void draw(sf::RenderWindow& window);  // Method to draw the grid
};
