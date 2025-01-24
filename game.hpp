#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "blocks.cpp"

class Game{
    public:
        Game();
        Grid grid;
        bool gameOver;

        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void Draw(sf::RenderWindow &window);
        void HandleInput(sf::RenderWindow &window);

        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        void InstantDrop();

       private:
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();

};
