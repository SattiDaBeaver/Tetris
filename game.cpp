#include "game.hpp"
#include <random>
#include <optional>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
} 

Block Game::GetRandomBlock(){
    if (blocks.empty()){
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), LBlock(), JBlock(), ZBlock(), SBlock(), OBlock(), TBlock()};
}

void Game::Draw(sf::RenderWindow &window){
    grid.Draw(window);
    currentBlock.Draw(window);
}

void Game::HandleInput(sf::RenderWindow &window){
    std::optional event = window.pollEvent();
    if (gameOver && event->getIf<sf::Event::KeyPressed>()){
        gameOver = false;
        Reset();
    }
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
        switch(keyPressed->scancode){
            case(sf::Keyboard::Scan::A):
                MoveBlockLeft();
                break;

            case(sf::Keyboard::Scan::D):
                MoveBlockRight();
                break;

            case(sf::Keyboard::Scan::S):
                MoveBlockDown();
                break;

            case(sf::Keyboard::Scan::W):
                RotateBlock();
                break;
                
            case(sf::Keyboard::Scan::Space):
                InstantDrop();
                break;
        }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)){
        //     MoveBlockLeft();
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)){
        //     MoveBlockRight();
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)){
        //     MoveBlockDown();
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){
        //     RotateBlock();
        // }
    }
}

void Game::MoveBlockLeft(){
    if (gameOver == false){
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight(){
    if (gameOver == false){
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown(){
    if (gameOver == false){
    currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::InstantDrop(){
    if (gameOver == false){
        while (IsBlockOutside() == false && BlockFits()){
            currentBlock.Move(1, 0);
        }
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if (grid.IsCellOutside(item.row, item.col)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if (gameOver == false){
        currentBlock.Rotate();
        if (IsBlockOutside()  || BlockFits() == false){
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    grid.ClearFullRows();
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        if(grid.IsCellEmpty(item.row, item.col) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}
