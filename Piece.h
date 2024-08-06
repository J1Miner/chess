#pragma once

#include <SFML/Graphics.hpp>

class Piece {
public:
    int x;
    int y;
    bool isKing;
    sf::Texture& texture;
    sf::Sprite  sprite;

    sf::Color color;
    bool isAlive;

    Piece(int x = 0, int y = 0, sf::Color color = sf::Color::White,sf::Texture & texture);

    void Draw(sf::RenderWindow& window) const;
};