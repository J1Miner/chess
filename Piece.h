#pragma once
#include <SFML/Graphics.hpp>

enum Type {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

class Piece {
public:
    // Static textures for all piece types
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

    // Piece attributes
    int x;
    int y;
    bool isKing = false;
    sf::Texture* texture = nullptr;
    Type pieceType = PAWN;
    bool firstTurn = true;
    sf::Color color;
    bool isAlive = true;

    // Constructors
    Piece();
    Piece(int x, int y, sf::Color color, Type pieceType);

    // Methods
    void Draw(sf::RenderWindow& window);
    void setTexture();

    // Static method to load textures
    static void loadStaticTextures();
};

