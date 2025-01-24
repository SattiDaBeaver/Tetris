#include "block.hpp"

Block::Block() {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw(sf::RenderWindow &window) {
    std::vector<Position> tiles = GetCellPosition();
    for (Position item : tiles) {
        sf::RectangleShape renderCell({(float)(cellSize - 1), (float)(cellSize - 1)});
        renderCell.setPosition({(float)(item.col * cellSize + 11), (float)(item.row * cellSize + 11)});
        renderCell.setFillColor(colors[id]);
        window.draw(renderCell);
    }
}

void Block::Move(int rows, int cols){
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::GetCellPosition(){
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate(){
    rotationState++;
    if (rotationState == (int)cells.size()){
        rotationState = 0;
    }
}

void Block::UndoRotation(){
    rotationState--;
    if (rotationState == -1){
        rotationState = cells.size() - 1;
    }
}


