#include "MainScreen.h"
#include "Grid.h"

void MainScreen::update()
{
    if (screenState == ScreenState::Start && clock.getElapsedTime().asSeconds() >= 2.f)
    {
        screenState = ScreenState::Menu;
    }

    if (screenState == ScreenState::Level)
    {
        float deltaTime = clock.restart().asSeconds();

        player->update(deltaTime, enemies, 10); // Update the player
        playerLivesText.setString("Lives: " + to_string(player->getLives()));
        playerScoreText.setString("Score: " + to_string(this->player->getScore()));

        // Check if all enemies are killed
        bool allEnemiesKilled = true;
        for (int i = 0; i < 10; ++i)
        {
            if (enemies[i] != nullptr && enemies[i]->isAlive())
            {
                allEnemiesKilled = false;
                break;
            }
        }

        // If all enemies are killed, show the gate
        if (allEnemiesKilled)
        {
            gateVisible = true;
        }

        const float bound = 20.0f; 

        if (gateVisible && abs(player->getPosition().x - gateSprite.getPosition().x) < bound && abs(player->getPosition().y - gateSprite.getPosition().y) < bound)
        {
            cout << "Gate reached by player. Transitioning to win state." << endl;
            screenState = ScreenState::Win; // Move to win screen
            clock.restart(); 
        }
    }
    else if (screenState == ScreenState::Win)
    {
        if (clock.getElapsedTime().asSeconds() >= 3.0f)
        {
            screenState = ScreenState::Exit; // Move to exit state after 2 seconds
            clock.restart();
        }
    }
    else if (menuOptions[selectedOption].getString() == "HIGHSCORE")
    {
        screenState = ScreenState::HighScore;
        loadHighScores(); // Load the high scores
    }

}


bool MainScreen::shouldClose() const
{
    return screenState == ScreenState::Exit && clock.getElapsedTime().asSeconds() >= 2.f;
}

void MainScreen::moveUp()
{
    if (selectedOption - 1 >= 0)
    {
        menuOptions[selectedOption].setFillColor(Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(Color::Green);
    }
}

void MainScreen::moveDown()
{
    if (selectedOption + 1 < menuSize)
    {
        menuOptions[selectedOption].setFillColor(Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(Color::Green);
    }
}
void MainScreen::handleMouseClick(float x, float y)
{
    if (screenState == ScreenState::Menu)
    {
        for (int i = 0; i < menuSize; ++i)
        {
            if (menuOptions[i].getGlobalBounds().contains(x, y))
            {
                menuOptions[selectedOption].setFillColor(Color::White);
                selectedOption = i;
                menuOptions[selectedOption].setFillColor(Color::Green);
                if (menuOptions[selectedOption].getString() == "EXIT GAME")
                {
                    screenState = ScreenState::Exit;
                    clock.restart();
                }
                else if (menuOptions[selectedOption].getString() == "HOW TO PLAY")
                {
                    screenState = ScreenState::HowToPlay;
                }
                else if (menuOptions[selectedOption].getString() == "START GAME")
                {
                    screenState = ScreenState::Level;
                }
                else if (menuOptions[selectedOption].getString() == "HIGH SCORE")
                {
                    screenState = ScreenState::HighScore;
                    loadHighScores(); // Load high scores
                }
            }
        }
    }
}


void MainScreen::handleMouseMove(float x, float y)
{
    if (screenState == ScreenState::Menu)
    {
        for (int i = 0; i < menuSize; ++i)
        {
            if (menuOptions[i].getGlobalBounds().contains(x, y))
            {
                if (selectedOption != i)
                {
                    menuOptions[selectedOption].setFillColor(Color::White);
                    selectedOption = i;
                    menuOptions[selectedOption].setFillColor(Color::Green);
                }
                return; // Exit the function once a match is found
            }
        }
    }
}

void MainScreen::draw(RenderWindow& window)
{
    if (screenState == ScreenState::Start)
    {
        window.draw(startSprite); // Draw the starting screen
    }
    else if (screenState == ScreenState::Menu)
    {
        window.draw(backgroundSprite);
        for (int i = 0; i < menuSize; ++i)
        {
            window.draw(menuOptions[i]);
        }
    }
    else if (screenState == ScreenState::Exit)
    {
        window.draw(exitSprite); // Draw the exit screen
    }
    else if (screenState == ScreenState::HowToPlay)
    {
        window.draw(howToPlaySprite); // Draw the How to Play screen
    }
    else if (screenState == ScreenState::Level)
    {
        window.draw(levelSprite); // Draw the Level screen
        Grid grid;  // Create a grid object
        grid.draw(window);

        window.draw(playerLivesText);
        window.draw(playerScoreText);

        player->draw(window); // Draw the player
        for (int i = 0; i < 10; ++i)
        {
            if (enemies[i] != nullptr)
            {
                enemies[i]->draw(window);
            }
        }
        if (gateVisible)
        {
            window.draw(gateSprite);
        }
    }
    else if (screenState == ScreenState::HighScore)
    {
        window.draw(backgroundSprite); 
        for (int i = 0; i < 5; ++i)
        {
            window.draw(highScoresText[i]);
        }
    }
    else if (screenState == ScreenState::Win)
    {
        window.draw(winSprite); // Draw the win screen
    }
}



void MainScreen::goBackToMenu()
{
    screenState = ScreenState::Menu;
}

MainScreen::ScreenState MainScreen::getScreenState() const
{
    return this->screenState;
}

void MainScreen::handleInput(float deltaTime)
{
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        player->handleInput(deltaTime); // Move up
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        player->handleInput(deltaTime); // Move down
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        player->handleInput(deltaTime); // Move left
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        player->handleInput(deltaTime); // Move right
    }
}