#include <SFML/Graphics.hpp>
#include "board.h"
#include "piece.h"
#include "game.h"

//hello John
//TODO: initialize loadTexture function here
sf::Texture bBishopTex;
sf::Texture bKingTex;
sf::Texture bKnightTex;
sf::Texture bPawnTex;
sf::Texture bQueenTex;
sf::Texture bRookTex;
sf::Texture wBishopTex;
sf::Texture wKingTex;
sf::Texture wKnightTex;
sf::Texture wPawnTex;
sf::Texture wQueenTex;
sf::Texture wRookTex;

void loadTexture() {
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

int main() {
    // Setup the SFML window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess");
    window.setFramerateLimit(60);

    // Initialize board and pieces
    Board board;
    Piece blackPieces[12];
    Piece whitePieces[12];
    Game game;
    game.Setup(blackPieces, whitePieces);

    // Game state variables
    int turn = 0;  // 0 for Black, 1 for White
    int selectedX = -1;
    int selectedY = -1;
    bool isPieceSelected = false;
    bool pieceHasJumped = false;

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                game.ProcessTurn(turn, mousePos, blackPieces, whitePieces, selectedX, selectedY, isPieceSelected, pieceHasJumped);
            }
        }

        // Clear the window
        window.clear();

        // Draw board and pieces
        board.Draw(window);
        for (const Piece& piece : blackPieces) {
            piece.Draw(window);
        }
        for (const Piece& piece : whitePieces) {
            piece.Draw(window);
        }

        // Highlight the selected piece and available moves
        if (isPieceSelected) {
            board.HighlightSelectedPiece(window, selectedX, selectedY);

            // Get available moves and highlight them
            Piece* selectedPiece = game.FindPiece(selectedX, selectedY, blackPieces, whitePieces);
            std::vector<std::pair<int, int>> availableMoves = game.GetAvailableMoves(selectedPiece, blackPieces, whitePieces);
            for (const auto& move : availableMoves) {
                board.HighlightMove(window, move.first, move.second);
            }
        }

        // Display the window
        window.display();
    }

    return 0;
}

//TODO: Define loadTexture function here