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

Piece::Piece() : x(0), y(0), color(sf::Color::Black), pieceType(PAWN), isAlive(true), isKing(false), firstTurn(true), texture(nullptr) {}

Piece::Piece(int x, int y, sf::Color color, Type pieceType) : x(x), y(y), color(color), pieceType(pieceType), isAlive(true), isKing(false), firstTurn(true) {
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
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setScale(60. / 133., 60. / 133.);
        sprite.setPosition(sf::Vector2f(x * 75 + 7, y * 75 + 7));
        window.draw(sprite);

        // Optionally draw a king marker if the piece is a king
        if (isKing) {
            sf::CircleShape crown(10.f);
            crown.setFillColor(sf::Color::Yellow);  // Example color for king marker
            crown.setPosition(sf::Vector2f(x * 75 + 32, y * 75 + 32));  // Center it
            window.draw(crown);
        }
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

