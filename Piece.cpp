#include "Piece.h"
#include <iostream>

// Define static member variables
sf::Texture Piece::bBishopTex;
sf::Texture Piece::bKingTex;
sf::Texture Piece::bKnightTex;
sf::Texture Piece::bPawnTex;
sf::Texture Piece::bQueenTex;
sf::Texture Piece::bRookTex;
sf::Texture Piece::wBishopTex;
sf::Texture Piece::wKingTex;
sf::Texture Piece::wKnightTex;
sf::Texture Piece::wPawnTex;
sf::Texture Piece::wQueenTex;
sf::Texture Piece::wRookTex;

Piece::Piece() {
    x = 0;
    y = 0;
    color = sf::Color::White;
    pieceType = PAWN;
}

Piece::Piece(int x, int y, sf::Color color, Type pieceType){
    this->x = x;
    this->y = y;
    this->color = color;
    this->pieceType = pieceType;
    setTexture();
}

void Piece::setTexture() {
    if (color == sf::Color::White) {
        switch (pieceType) {
        case BISHOP:
            texture = &wBishopTex;
            break;
        case KING:
            texture = &wKingTex;
            break;
        case KNIGHT:
            texture = &wKnightTex;
            break;
        case PAWN:
            texture = &wPawnTex;
            break;
        case QUEEN:
            texture = &wQueenTex;
            break;
        case ROOK:
            texture = &wRookTex;
            break;
        }
    }
    else {
        switch (pieceType) {
        case BISHOP:
            texture = &bBishopTex;
            break;
        case KING:
            texture = &bKingTex;
            break;
        case KNIGHT:
            texture = &bKnightTex;
            break;
        case PAWN:
            texture = &bPawnTex;
            break;
        case QUEEN:
            texture = &bQueenTex;
            break;
        case ROOK:
            texture = &bRookTex;
            break;
        }
    }
}

void Piece::Draw(sf::RenderWindow& window) {
    if (isAlive) {
        //sf::CircleShape shape(30.f);
        //shape.setFillColor(color);
        std::cout << "trying to draw piece\n";
        std::cout << "Color : ";
        if (color == sf::Color::White)
            std::cout << "White\n";
        else
            std::cout << "Black\n";
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setScale(60. / 133., 60./133.);
        sprite.setPosition(sf::Vector2f(x * 75 + 7, y * 75 + 7));
        window.draw(sprite);

       /*if (isKing) {
            shape.setFillColor(sf::Color::Green);
            shape.setRadius(10.f);
            shape.setPosition(sf::Vector2f(x * 75 + 30, y * 75 + 30));
            window.draw(shape);
        }*/
    }
}
void Piece::loadStaticTextures() {
    bBishopTex.loadFromFile("resources/sprites/bBishop.png");
    bKingTex.loadFromFile("resources/sprites/bKing.png");
    bKnightTex.loadFromFile("resources/sprites/bKnight.png");
    bPawnTex.loadFromFile("resources/sprites/bPawn.png");
    bQueenTex.loadFromFile("resources/sprites/bQueen.png");
    bRookTex.loadFromFile("resources/sprites/bRook.png");
    wBishopTex.loadFromFile("resources/sprites/wBishop.png");
    wKingTex.loadFromFile("resources/sprites/wKing.png");
    wKnightTex.loadFromFile("resources/sprites/wKnight.png");
    wPawnTex.loadFromFile("resources/sprites/wPawn.png");
    wQueenTex.loadFromFile("resources/sprites/wQueen.png");
    wRookTex.loadFromFile("resources/sprites/wRook.png");
}

