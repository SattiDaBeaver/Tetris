#pragma once
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"

class Block{
    public:
        Block();
        int id;

        void Draw(sf::RenderWindow& window, int offsetX, int offsetY);
        void Move(int rows, int cols);
        std::vector<Position> GetCellPosition();
        void Rotate();
        std::map<int, std::vector<Position>> cells;
        void UndoRotation();

    private:
        int cellSize;
        int rotationState;
        std::vector<sf::Color> colors;
        int rowOffset;
        int colOffset;
};