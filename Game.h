#pragma once
#include "board.h"
#include "piece.h"

class Game {
public:
    void Setup(Piece* whitePieces, Piece* blackPieces);

    bool IsKingInCheck(Piece* king, Piece* whitePieces, Piece* blackPieces);

    Piece* FindPieceOfType(Type type, Piece* pieces);

    Piece* FindPiece(int x, int y, Piece* whitePieces, Piece* blackPieces);
    void KillPiece(int x, int y, Piece* whitePieces, Piece* blackPieces);
    std::vector<std::pair<int, int>> GetAvailableJumps(Piece* piece, Piece* whitePieces, Piece* blackPieces);
    std::vector<std::pair<int, int>> GetAvailableMoves(Piece* piece, Piece* whitePieces, Piece* blackPieces);
    void MovePiece(Piece* piece, int newX, int newY, Piece* whitePieces, Piece* blackPieces, bool isJump);
    void ProcessTurn(int& turn, sf::Vector2i mousePos, Piece* whitePieces, Piece* blackPieces, int& selectedX, int& selectedY, bool& isPieceSelected, bool& pieceHasJumped);
    void HighlightSelectedPiece(sf::RenderWindow& window, int x, int y) const;
    void HighlightMove(sf::RenderWindow& window, int x, int y) const;
};