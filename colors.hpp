#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

extern const sf::Color darkGrey;
extern const sf::Color green;
extern const sf::Color red;
extern const sf::Color orange;
extern const sf::Color yellow;
extern const sf::Color purple;
extern const sf::Color cyan;
extern const sf::Color blue;
extern const sf::Color lightBlue;
extern const sf::Color darkBlue;

std::vector<sf::Color> GetCellColors();
