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
        bool IsCellOutside(int row, int col);
        bool IsCellEmpty(int row, int col);
        int ClearFullRows();

    private:
        int numRows;
        int numCols;
        int cellSize;
        std::vector<sf::Color> colors;
        bool IsRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);
};