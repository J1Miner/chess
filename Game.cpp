#include "game.h"

void Game::Setup(Piece* blackPieces, Piece* whitePieces) {
    //Piece::loadStaticTextures();
    for (int i = 0; i < 8; i++) {
        
            whitePieces[i] = Piece(i, 1, sf::Color::White, PAWN);
        
    }


    for (int i = 0; i < 8; i++) {
       
            blackPieces[i] = Piece(i, 6, sf::Color::Black, PAWN);

    }
}

Piece* Game::FindPiece(int x, int y, Piece* blackPieces, Piece* whitePieces) {
    for (int i = 0; i <= 8; i++) {
        if ((blackPieces[i].x == x && blackPieces[i].y == y && blackPieces[i].isAlive) ||
            (whitePieces[i].x == x && whitePieces[i].y == y && whitePieces[i].isAlive)) {
            return (blackPieces[i].x == x && blackPieces[i].y == y) ? &blackPieces[i] : &whitePieces[i];
        }
    }
    return nullptr;
}

void Game::KillPiece(int x, int y, Piece* blackPieces, Piece* whitePieces) {
    Piece* pieceToKill = FindPiece(x, y, blackPieces, whitePieces);
    if (pieceToKill != nullptr) {
        pieceToKill->isAlive = false;
    }
}

std::vector<std::pair<int, int>> Game::GetAvailableJumps(Piece* piece, Piece* blackPieces, Piece* whitePieces) {
    std::vector<std::pair<int, int>> availableJumps;
    int directions[4][2] = { {2, 2}, {2, -2}, {-2, 2}, {-2, -2} };

    for (int i = 0; i < 4; i++) {
        int newX = piece->x + directions[i][0];
        int newY = piece->y + directions[i][1];
        int midX = piece->x + directions[i][0] / 2;
        int midY = piece->y + directions[i][1] / 2;

        // Ensure the jump is within bounds
        if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
            Piece* middlePiece = FindPiece(midX, midY, blackPieces, whitePieces);
            Piece* destPiece = FindPiece(newX, newY, blackPieces, whitePieces);

            // Only allow jumps over opponent pieces to an empty square
            if (middlePiece != nullptr && middlePiece->color != piece->color && destPiece == nullptr) {
                // Ensure backward jumps are only allowed for kings
                if (piece->isKing || (piece->color == sf::Color::White && newY > piece->y) || (piece->color == sf::Color::Black && newY < piece->y)) {
                    availableJumps.push_back({ newX, newY });
                }
            }
        }
    }

    return availableJumps;
}

std::vector<std::pair<int, int>> Game::GetAvailableMoves(Piece* piece, Piece* blackPieces, Piece* whitePieces) {
    std::vector<std::pair<int, int>> availableMoves;
    //std::vector<std::pair<int, int>> availableJumps = GetAvailableJumps(piece, blackPieces, whitePieces);

    // If there are available jumps, return only the jumps
    /*if (!availableJumps.empty()) {
        return availableJumps;
    }*/

    // Define directions for movement
    std::vector<std::pair<int, int>> directions;

    // Add forward directions based on piece color
    if (piece->color == sf::Color::White) {
        // White pieces move forward (downward)
        directions.push_back({ 0,1});  // forward-right

        // Allow backward directions if the piece is king
        if (piece->isKing) {
            directions.push_back({ -1, -1 }); // backward-left
            directions.push_back({ 1, -1 });  // backward-right
        }
    }
    else if (piece->color == sf::Color::Black) {
        // Black pieces move forward (upward)
         // forward-left
        directions.push_back({ 0,-1 });  // forward-right

        // Allow backward directions if the piece is king
        if (piece->isKing) {
            directions.push_back({ 1,1 }); // backward-left
            directions.push_back({ -1,-1 });  // backward-right
        }
    }

    // Iterate through the possible directions and check for valid moves
    for (const auto& dir : directions) {
        int newX = piece->x + dir.first;
        int newY = piece->y + dir.second;

        if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
            Piece* destPiece = FindPiece(newX, newY, blackPieces, whitePieces);
            if (destPiece == nullptr) {
                // Empty square - add as available move
                availableMoves.push_back({ newX, newY });
            }
        }
    }

    return availableMoves;
}

void Game::MovePiece(Piece* piece, int newX, int newY, Piece* blackPieces, Piece* whitePieces, bool isJump) {
    // If it was a jump, kill the jumped piece
    

    // Update piece position
    piece->x = newX;
    piece->y = newY;

    // Crown the piece if it reaches the last row
    if ((piece->color == sf::Color::White && piece->y == 7) ||
        (piece->color == sf::Color::Black && piece->y == 0)) {
        piece->isKing = true;
    }
}

void Game::HighlightSelectedPiece(sf::RenderWindow& window, int x, int y) const {
    sf::CircleShape highlight(30.f);
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineThickness(3.f);
    highlight.setOutlineColor(sf::Color::Green);
    highlight.setPosition(75 * x + 7.5f, 75 * y + 7.5f);
    window.draw(highlight);
}

void Game::HighlightMove(sf::RenderWindow& window, int x, int y) const {
    sf::CircleShape highlight(30.f);
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineThickness(3.f);
    highlight.setOutlineColor(sf::Color::Blue);
    highlight.setPosition(75 * x + 7.5f, 75 * y + 7.5f);
    window.draw(highlight);
}

void Game::ProcessTurn(int& turn, sf::Vector2i mousePos, Piece* blackPieces, Piece* whitePieces, int& selectedX, int& selectedY, bool& isPieceSelected, bool& pieceHasJumped) {
    int clickedX = mousePos.x / 75;
    int clickedY = mousePos.y / 75;

    if (isPieceSelected) {
        Piece* selectedPiece = FindPiece(selectedX, selectedY, blackPieces, whitePieces);

        // Check if the clicked position is the same as the selected piece's position
        if (clickedX == selectedX && clickedY == selectedY) {
            // Allow deselection only if the piece hasn't jumped or there are no more available jumps
            if (!pieceHasJumped || GetAvailableJumps(selectedPiece, blackPieces, whitePieces).empty()) {
                isPieceSelected = false;
                selectedX = -1;
                selectedY = -1;
                pieceHasJumped = false;
            }
            return;
        }

        // Process the move
        std::vector<std::pair<int, int>> availableMoves = GetAvailableMoves(selectedPiece, blackPieces, whitePieces);
        bool validMove = false;
        bool isJump = false;

        // Check if the clicked position is a valid move
        for (const auto& move : availableMoves) {
            if (move.first == clickedX && move.second == clickedY) {
                validMove = true;
                // If the move is a jump, set the flag to true
                if (std::abs(selectedPiece->x - clickedX) > 1) {
                    isJump = true;
                }
                break;
            }
        }

        if (validMove) {
            MovePiece(selectedPiece, clickedX, clickedY, blackPieces, whitePieces, isJump);

            // Check for available jumps after the move
            std::vector<std::pair<int, int>> newAvailableJumps = GetAvailableJumps(selectedPiece, blackPieces, whitePieces);
            if (isJump && !newAvailableJumps.empty()) {
                // Keep the piece selected if there are further jumps available
                selectedX = clickedX;
                selectedY = clickedY;
                pieceHasJumped = true;
            }
            else {
                // Switch turns if there are no further jumps
                turn = 1 - turn;
                isPieceSelected = false;
                pieceHasJumped = false;
            }
        }
    }
    else {
        // Select a piece
        Piece* clickedPiece = FindPiece(clickedX, clickedY, blackPieces, whitePieces);
        if (clickedPiece && clickedPiece->isAlive && clickedPiece->color == (turn == 0 ? sf::Color::Black : sf::Color::White)) {
            std::vector<std::pair<int, int>> availableMoves = GetAvailableMoves(clickedPiece, blackPieces, whitePieces);

            // Check if there are any available moves
            if (!availableMoves.empty()) {
                selectedX = clickedX;
                selectedY = clickedY;
                isPieceSelected = true;
                pieceHasJumped = false; // Reset jump flag for new piece selection
            }
        }
    }
}