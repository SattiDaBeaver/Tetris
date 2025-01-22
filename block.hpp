#pragma once
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"

class Block{
    public:
        Block();
        void Draw(sf::RenderWindow& window);
        int id;
        std::map<int, std::vector<Position>> cells;
    private:
        int cellSize;
        int rotationState;
        std::vector<sf::Color> colors;
        
};