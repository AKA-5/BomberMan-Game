#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainScreen.h"
#include<fstream>           // file handling
#include "Player.h"
#include"Enemy.h"


// helper function to create and store file scores
void updateHighScores(int newScore)
{
    int highScores[6] = { 0 }; // 6 to include the new score
    int count = 0;

    ifstream inputFile("highscores.txt");
    while (inputFile >> highScores[count] && count < 5)
    {
        count++;
    }
    inputFile.close();

    highScores[count] = newScore;

    // Bubble Sort to sort the array in descending order
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j <= count; j++)
        {
            if (highScores[i] < highScores[j])
            {
                // Swap the elements
                int temp = highScores[i];
                highScores[i] = highScores[j];
                highScores[j] = temp;
            }
        }
    }

    // Determine the number of scores to write (max 5)
    int scoresToWrite = (count < 5) ? (count + 1) : 5;

    ofstream outputFile("highscores.txt");
    for (int i = 0; i < scoresToWrite; i++)
    {
        outputFile << highScores[i] << endl;
    }
    outputFile.close();
}


int main()
{
    RenderWindow window(VideoMode(600, 600), "AK BOMBERMAN");
    MainScreen mainScreen;

    Player player(20, 20, 1.0f);
    int score = 0;
    // Loading bg music
    Music backgroundMusic;

    if (!backgroundMusic.openFromFile("./music/bg.wav"))
    {
        cout << "\nError in loading music" << endl;
    }
    sf::Clock clock;

    // Play the music
    backgroundMusic.setLoop(true); // Loop the music
    backgroundMusic.setVolume(30); 
    backgroundMusic.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (mainScreen.getScreenState() == MainScreen::ScreenState::Menu)
                    {
                        window.close();
                    }
                    else
                    {
                        mainScreen.goBackToMenu();
                    }
                }
                if (event.key.code == sf::Keyboard::Up)
                    mainScreen.moveUp();
                if (event.key.code == sf::Keyboard::Down)
                    mainScreen.moveDown();
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (mainScreen.shouldClose())
                        window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mainScreen.handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                mainScreen.handleMouseMove(event.mouseMove.x, event.mouseMove.y);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        mainScreen.update(); // Update the screen state
        player.update(deltaTime, mainScreen.getEnemies(), 10);
        window.clear();
        mainScreen.draw(window);
        window.display();

        if (mainScreen.shouldClose())
        {
            cout << "\nPlayer class Score: " << player.getScore() << endl;
            if(player.getScore() != 0)
            {
                score = 200 - player.getScore();  // for storing and displaying score
            }
            else
            {
                score = 0;
            }

            window.close();
        }
    }

    backgroundMusic.stop();
    cout << "\nPlayer Score: " << score << endl;
    updateHighScores(score);

    return 0;
}