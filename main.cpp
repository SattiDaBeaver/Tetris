#include <optional>
#include "game.hpp"
#include "grid.hpp"

int main(int argc, char* argv[]){
    sf::Color darkBlue = {44, 44, 127, 255};

    sf::RenderWindow window(sf::VideoMode({300, 600}), "Tetris!");
    window.setFramerateLimit(60);

    Grid grid = Grid();
    grid.Print();

    while(window.isOpen()){

        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen
        window.clear(darkBlue);
        grid.Draw(window);

        window.display();
    }

    return 0;
}