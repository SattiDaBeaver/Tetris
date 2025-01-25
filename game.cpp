#include "game.hpp"
#include <random>
#include <time.h>
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
    time_t seed;
    time(&seed);
    srand((unsigned int)seed);
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
    currentBlock.Draw(window, 11, 11);
    switch(nextBlock.id){
        case 3:
            nextBlock.Draw(window, 255, 290);
            break;
        case 7:
            nextBlock.Draw(window, 255, 280);
            break;
        default:
            nextBlock.Draw(window, 270, 270);
    }
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
                UpdateScore(0, 1);
                break;

            case(sf::Keyboard::Scan::W):
                RotateBlock();
                break;
                
            case(sf::Keyboard::Scan::Space):
                InstantDrop();
                UpdateScore(0, 10);
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
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
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
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 600;
        break;
    case 4:
        score += 1000;
        break;

    default:
        break;
    }

    score += moveDownPoints;
}
