#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Grid{
    public:
        Grid();
        void Initialize();
        void Print();
        void Draw(sf::RenderWindow &window);
        int grid[20][10];


    private:
        std::vector<sf::Color> GetCellColors();
        int numRows;
        int numCols;
        int cellSize;
        std::vector<sf::Color> colors;
};