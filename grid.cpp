#include "grid.hpp"
#include <iostream>

Grid::Grid(){
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    colors = GetCellColors();
    Initialize();
}

void Grid::Initialize(){
    for (int row = 0; row < numRows; row++){
        for (int col = 0; col < numCols; col++){
            grid[row][col] = 0;
        }
    }
}

void Grid::Print(){
    for (int row = 0; row < numRows; row++){
        for (int col = 0; col < numCols; col++){
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<sf::Color> Grid::GetCellColors(){
    sf::Color darkGrey = {26, 31, 40, 255};
    sf::Color green = {47, 230, 23, 255};
    sf::Color red = {232, 18, 18, 255};
    sf::Color orange = {226, 116, 17, 255};
    sf::Color yellow = {237, 234, 4, 255};
    sf::Color purple = {166, 0, 247, 255};
    sf::Color cyan = {21, 204, 29, 255};
    sf::Color blue = {13, 64, 216, 255};

    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

void Grid::Draw(sf::RenderWindow &window){
    for (int row = 0; row < numRows; row++){
        for (int col = 0; col < numCols; col++){
            int cellValue = grid[row][col];
            sf::RectangleShape renderCell({(float)(cellSize - 1), (float)(cellSize - 1)});
            renderCell.setPosition({(float)(col * cellSize + 1), (float)(row * cellSize + 1)});
            renderCell.setFillColor(colors[cellValue]);
            window.draw(renderCell);
        }
    }
}