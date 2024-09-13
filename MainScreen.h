#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include"Enemy.h"
#include<fstream>
#include <iostream>
#include <ctime> // For random enemies location

using namespace std;
using namespace sf;

class MainScreen
{
private:
    Font font;
    Text playerLivesText; // Text to display player's lives
    Text playerScoreText; // Text to display player's score

    Text menuOptions[4]; // Array to hold the menu options
    const int menuSize = 4;  // Number of menu options
    int selectedOption;

    Texture backgroundTexture; // Texture for the background image
    Sprite backgroundSprite;   // Sprite for the background image

    // Starting screen
    Texture startTexture; // Texture for the starting screen image
    Sprite startSprite;   // Sprite for the starting screen image

    // Exit screen
    Texture exitTexture; // Texture for the image to display for a few seconds
    Sprite exitSprite;   // Sprite for the image to display
    Clock clock;            // Clock to track elapsed time

    // How to Play screen
    Texture howToPlayTexture;
    Sprite howToPlaySprite;

    // Level screen
    Texture levelTexture;
    Sprite levelSprite;

    Texture blockTexture;
    Texture woodTexture;
    Sprite blockSprite;
    Sprite woodSprite;

    // Player-related
    Texture playerTexture; // Texture for the player
    Player* player; // Pointer to the player object

    Enemy* enemies[10]; // Array of pointers to enemies


    Texture gateTexture;
    Sprite gateSprite;
    bool gateVisible = false;  // Initially, the gate is not visible
    Texture winTexture;
    Sprite winSprite;

    Text highScoresText[5]; 
public:

    enum class ScreenState { Start, Menu, Exit, HowToPlay, Level, Win, HighScore };
    ScreenState screenState;    // Current screen state

    MainScreen()
    {
        
        // Load the font
        if (!font.loadFromFile("./fonts/arial.ttf"))
        {
            cout << "\nMenu Screen Fonts not Loaded!" << endl;
        }
        if (!backgroundTexture.loadFromFile("./images/background.png"))
        {
            cout << "\nBackground Image not Loaded!" << endl;
        }

        // Set the texture to the sprite
        backgroundSprite.setTexture(backgroundTexture);


        // Load the texture for the starting screen image
        if (!startTexture.loadFromFile("./images/start1.png"))
        {
            cout << "\nStarting Screen Image not Loaded!" << endl;
        }
        startSprite.setTexture(startTexture);


        // Load the texture for the image to display for a few seconds
        if (!exitTexture.loadFromFile("./images/exit.png"))
        {
            cout << "\nExit Screen Image not Loaded!" << endl;
        }

        // Set the texture to the sprite
        exitSprite.setTexture(exitTexture);

        // Load the texture for the level screen image
        if (!levelTexture.loadFromFile("./images/level.png"))
        {
            cout << "\nLevel Screen Image not Loaded!" << endl;
        }
        levelSprite.setTexture(levelTexture);

        // Load the texture for the How to Play screen image
        if (!howToPlayTexture.loadFromFile("./images/howtoplay.png"))
        {
            cout << "\nHow to Play Screen Image not Loaded!" << endl;
        }
        howToPlaySprite.setTexture(howToPlayTexture);

        // Initialize the player with the loaded texture
        player = new Player(20, 20, 1.f); 

        for (int i = 0; i < 10; ++i)
        {
            enemies[i] = new Enemy();
            enemies[i]->generateRandomPosition(player->getPosition(), enemies, 10);
        }

        // Load the texture for block
        if (!blockTexture.loadFromFile("./images/block.png"))
        {
            cout << "\nblock Image not Loaded!" << endl;
        }
        // Set the texture to the sprite for block
        blockSprite.setTexture(blockTexture);

        // Load the texture for wood
        if (!woodTexture.loadFromFile("./images/wood.png"))
        {
            cout << "\nwood Image not Loaded!" << endl;
        }
       
        // Set the texture to the sprite for wood
        woodSprite.setTexture(woodTexture);

        if (!gateTexture.loadFromFile("./images/gate.png"))
        {
            cout << "\nGate Image not Loaded!" << endl;
        }
        gateSprite.setTexture(gateTexture);

        gateSprite.setPosition(280.f, 540.f); 

        for (int i = 0; i < 5; ++i)
        {
            highScoresText[i].setFont(font);
            highScoresText[i].setCharacterSize(36);
            highScoresText[i].setFillColor(Color::White);
        }

        if (!winTexture.loadFromFile("./images/win.png"))
        {
            cout << "\nWin Screen Image not Loaded!" << endl;
        }
        winSprite.setTexture(winTexture);

        selectedOption = 0; 

        for (int i = 0; i < menuSize; ++i)
        {
            menuOptions[i].setFont(font);
            menuOptions[i].setCharacterSize(48);
            menuOptions[i].setFillColor(Color::White);
            menuOptions[i].setOutlineThickness(3);
            if (i == 0)
                menuOptions[i].setString("START GAME");
            if (i == 1)
                menuOptions[i].setString("HOW TO PLAY");
            if (i == 2)
                menuOptions[i].setString("HIGH SCORE");
            if (i == 3)
                menuOptions[i].setString("EXIT GAME");

            menuOptions[i].setPosition(150.f, 200.f + i * 70.f); 
        }
        menuOptions[0].setFillColor(Color::Green); // Highlight the first option

        screenState = ScreenState::Start; // Initialize the screen state to menu
        clock.restart(); 

        // player score and live text
        playerLivesText.setFont(font);
        playerLivesText.setCharacterSize(20);
        playerLivesText.setFillColor(Color::White);
        playerLivesText.setOutlineThickness(1);
        playerLivesText.setPosition(40.f, 0.f); 

        playerScoreText.setFont(font);
        playerScoreText.setCharacterSize(20);
        playerScoreText.setFillColor(Color::White);
        playerScoreText.setOutlineThickness(1);
        playerScoreText.setPosition(300.f, 0.f);
    }
    void moveUp();
    void moveDown();
    void handleMouseClick(float x, float y);
    void handleMouseMove(float x, float y);
    void update();
    void draw(RenderWindow& window);
    bool shouldClose() const;
    void goBackToMenu();
    ScreenState getScreenState() const;
    void handleInput(float deltaTime); // Handle player input
    Enemy** getEnemies()
    {
        return &enemies[0];
    }


    void loadHighScores()
    {
        ifstream inputFile("highscores.txt");
        if (!inputFile.is_open())
        {
            cout << "\nFailed to open high scores file!" << endl;
            return;
        }

        string line;
        int index = 0;
        while (getline(inputFile, line) && index < 5)
        {
            highScoresText[index].setFont(font);
            highScoresText[index].setCharacterSize(36); // Set size of the font
            highScoresText[index].setFillColor(Color::White);
            highScoresText[index].setString(line);

            // Center the text horizontally on the screen
            highScoresText[index].setPosition(300.f - highScoresText[index].getLocalBounds().width / 2, 200.f + index * 50.f);
            index++;
        }
        inputFile.close();
    }


    ~MainScreen()
    {
        for (int i = 0; i < 10; ++i)
        {
            delete enemies[i];
        }
        delete player;
    }
};
