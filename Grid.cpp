#include "Grid.h"

Grid::Grid()
{
    // Allocate memory for the 2D array on the heap
    blocks = new sf::Sprite * [GRID_SIZE];
    for (unsigned int i = 0; i < GRID_SIZE; ++i)
    {
        blocks[i] = new sf::Sprite[GRID_SIZE];
    }

    // Load textures for the blocks
    if (!blockTexture.loadFromFile("./images/block.png") || !woodTexture.loadFromFile("./images/wood.png"))
    {
        std::cout << "\nFailed to load block textures." << std::endl;
    }

    blockSprite.setTexture(blockTexture);
    woodSprite.setTexture(woodTexture);

    // Initialize the grid
    initializeGrid();
}

void Grid::initializeGrid()
{
    for (unsigned int x = 0; x < GRID_SIZE; ++x)
    {
        for (unsigned int y = 0; y < GRID_SIZE; ++y)
        {
            sf::Sprite& sprite = blocks[x][y];
            // sprite.setTexture(woodTexture);
            sprite.setPosition(x * blockSize, y * blockSize);

            // Place blocks on the boundary
            if (x == 0 || x == GRID_SIZE - 1 || y == 0 || y == GRID_SIZE - 1)
            {
                sprite.setTexture(blockTexture);
            }
        }
    }
}

Grid::~Grid()
{
    // Deallocate memory for the 2D array
    for (unsigned int i = 0; i < GRID_SIZE; ++i)
    {
        delete[] blocks[i];
    }
    delete[] blocks;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (unsigned int x = 0; x < GRID_SIZE; ++x)
    {
        for (unsigned int y = 0; y < GRID_SIZE; ++y)
        {
            window.draw(blocks[x][y]);
        }
    }
}
