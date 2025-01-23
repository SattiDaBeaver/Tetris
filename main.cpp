#include <optional>
#include "game.hpp"
#include "grid.hpp"
#include "blocks.cpp"

int main(int argc, char* argv[]){
    sf::Color darkBlue = {44, 44, 127, 255};

    sf::RenderWindow window(sf::VideoMode({300, 600}), "Tetris!");
    window.setFramerateLimit(60);

    Grid grid = Grid();
    // Test
    LBlock lBlock = LBlock();
    IBlock iBlock = IBlock();
    JBlock jBlock = JBlock();
    OBlock oBlock = OBlock();
    TBlock tBlock = TBlock();
    SBlock sBlock = SBlock();
    ZBlock zBlock = ZBlock();

    //zBlock.Move(4, 3);

    // Test End

    grid.Print();

    while(window.isOpen()){

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
        grid.Draw(window);
        zBlock.Draw(window);

        // Render Display
        window.display();
    }

    return 0;
}