#include "grid.hpp"
#include <iostream>
#include "colors.hpp"

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