#pragma once

#include <SFML/Graphics.hpp>

class Piece {
public:
    //NEVER ACTUALLY USE THIS DEFAULT TEXTURE IT IS JUST HERE TO MAKE YOUR CODE HAPPY
    static sf::Texture defaultTex;
    int x;
    int y;
    bool isKing;
    sf::Texture* texture;
    sf::Sprite sprite;

    sf::Color color;
    bool isAlive;

    Piece(int x = 0, int y = 0, sf::Color color = sf::Color::White, sf::Texture* texture = nullptr);

    void Draw(sf::RenderWindow& window) const;
    void setTexture();
};