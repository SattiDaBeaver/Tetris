#include <optional>
#include "game.hpp"
#include "colors.hpp"

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

    scoreText.setCharacterSize(32);
    nextText.setCharacterSize(32);
    gameOverText.setCharacterSize(64);

    scoreText.setString("Score");
    nextText.setString("Next");
    gameOverText.setString("GAME OVER");

    scoreText.setPosition({365, 15});
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
        game.Draw(window);
        // Score n shit
        window.draw(scoreText);
        window.draw(nextText);
        window.draw(scoreRectangle);
        window.draw(nextRectangle);

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
