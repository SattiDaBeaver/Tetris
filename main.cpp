#include <optional>
#include "game.hpp"
#include "colors.hpp"
#include <iostream>

sf::Clock gameClock;

bool EventTriggered(double interval, sf::Time &lastUpdateTime){
    sf::Time currentTime = gameClock.getElapsedTime();
    double doubleTime = (double) currentTime.asMicroseconds() / 1000.f;
    if (doubleTime - lastUpdateTime.asMilliseconds() >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(int argc, char* argv[]){

    // Window Stuff
    sf::RenderWindow window(sf::VideoMode({500, 620}), "Tetris!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Game game = Game();
    
    // Font and Text
    sf::Font font("inter.ttf");

    sf::Text scoreText(font);
    sf::Text nextText(font);
    sf::Text gameOverText(font);
    sf::Text scoreNumText(font);

    scoreText.setCharacterSize(32);
    nextText.setCharacterSize(32);
    gameOverText.setCharacterSize(64);
    scoreNumText.setCharacterSize(38);

    scoreText.setString("Score");
    nextText.setString("Next");
    gameOverText.setString("GAME OVER");

    scoreText.setPosition({360, 15});
    nextText.setPosition({370, 175});
    gameOverText.setPosition({55, 250});

    // Shapes
    sf::RectangleShape scoreRectangle({170, 60});
    scoreRectangle.setPosition({320, 55});
    //scoreRectangle.setOutlineThickness(3);
    scoreRectangle.setFillColor(lightBlue);

    sf::RectangleShape nextRectangle({170, 180});
    nextRectangle.setPosition({320, 215});
    //scoreRectangle.setOutlineThickness(3);
    nextRectangle.setFillColor(lightBlue);

    sf::RectangleShape gameOverRectangle({400, 93});
    gameOverRectangle.setPosition({45, 245});
    //scoreRectangle.setOutlineThickness(3);
    gameOverRectangle.setFillColor(darkBlue);

    // Clock Variables
    sf::Time fallTime = gameClock.getElapsedTime();
    sf::Time inputTime = gameClock.getElapsedTime();

    while(window.isOpen()){

        // Game Stuff
            //if (EventTriggered(10, inputTime))
            game.HandleInput(window);
            
            if(EventTriggered(500, fallTime)){
                game.MoveBlockDown();
            }

            scoreNumText.setString(std::to_string(game.score));
            sf::FloatRect rect = scoreNumText.getLocalBounds();
            sf::Vector2f textWidth = rect.size;
            scoreNumText.setPosition({315 + (170 - textWidth.x) / 2, 60});
        // Window Stuff

        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)){
            window.close();
        }
 
        // Clear screen

        window.clear(darkBlue);

        // Draw Stuff
        
        // Score n shit
        window.draw(scoreText);
        window.draw(nextText);
        window.draw(scoreRectangle);
        window.draw(scoreNumText);
        window.draw(nextRectangle);

        game.Draw(window);

        if (game.gameOver){
            window.draw(gameOverRectangle);
            window.draw(gameOverText);
        }

        // Render Display
        window.display();
    }

    return 0;
}

// Functions
