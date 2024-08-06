#pragma once
#include "board.h"
#include "piece.h"

class Game {
public:
    void Setup(Piece* blackPieces, Piece* whitePieces);
    Piece* FindPiece(int x, int y, Piece* blackPieces, Piece* whitePieces);
    void KillPiece(int x, int y, Piece* blackPieces, Piece* whitePieces);
    std::vector<std::pair<int, int>> GetAvailableJumps(Piece* piece, Piece* blackPieces, Piece* whitePieces);
    std::vector<std::pair<int, int>> GetAvailableMoves(Piece* piece, Piece* blackPieces, Piece* whitePieces);
    void MovePiece(Piece* piece, int newX, int newY, Piece* blackPieces, Piece* whitePieces, bool isJump);
    void ProcessTurn(int& turn, sf::Vector2i mousePos, Piece* blackPieces, Piece* whitePieces, int& selectedX, int& selectedY, bool& isPieceSelected, bool& pieceHasJumped);
    void HighlightSelectedPiece(sf::RenderWindow& window, int x, int y) const;
    void HighlightMove(sf::RenderWindow& window, int x, int y) const;
};