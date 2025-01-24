#include <optional>
#include "game.hpp"

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
    sf::Color darkBlue = {44, 44, 127, 255};

    sf::RenderWindow window(sf::VideoMode({300, 600}), "Tetris!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Game game = Game();
    // Test
    

    // zBlock.Move(4, 3);

    // Test End

    // Clock Variables
    sf::Time fallTime = gameClock.getElapsedTime();
    sf::Time inputTime = gameClock.getElapsedTime();

    while(window.isOpen()){

        // Game Stuff
            //if (EventTriggered(10, inputTime))
            game.HandleInput(window);
            
            if(EventTriggered(100, fallTime)){
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

        // Render Display
        window.display();
    }

    return 0;
}

// Functions
