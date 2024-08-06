#pragma once
#include <SFML/Graphics.hpp>
enum Type {
    BISHOP,
    KING,
    KNIGHT,
    PAWN,
    QUEEN,
    ROOK
};
class Piece {
public:
    static sf::Texture bBishopTex;
    static sf::Texture bKingTex;
    static sf::Texture bKnightTex;
    static sf::Texture bPawnTex;
    static sf::Texture bQueenTex;
    static sf::Texture bRookTex;
    static sf::Texture wBishopTex;
    static sf::Texture wKingTex;
    static sf::Texture wKnightTex;
    static sf::Texture wPawnTex;
    static sf::Texture wQueenTex;
    static sf::Texture wRookTex;

    int x;
    int y;
    bool isKing = false;
    sf::Texture *texture = nullptr;
    Type pieceType = PAWN;

    sf::Color color;
    bool isAlive = true;
    Piece();
    Piece(int x, int y, sf::Color color, Type pieceType);

    void Draw(sf::RenderWindow& window);
    void setTexture();

    static void loadStaticTextures();
};