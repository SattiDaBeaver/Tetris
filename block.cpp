#include "block.hpp"

Block::Block(){
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
}

void Block::Draw(sf::RenderWindow &window){
    std::vector<Position> tiles = cells[rotationState];
    for(Position item: tiles){
        sf::RectangleShape renderCell({(float)(cellSize - 1), (float)(cellSize - 1)});
        renderCell.setPosition({(float)(item.col * cellSize + 1), (float)(item.row * cellSize + 1)});
        renderCell.setFillColor(colors[id]);
        window.draw(renderCell);
    }
}