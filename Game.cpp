#include "game.h"
#include "iostream"

void Game::Setup(Piece* whitePieces, Piece* blackPieces) {
    //Piece::loadStaticTextures();
    for (int i = 0; i < 8; i++) {
        
            blackPieces[i] = Piece(i, 1, sf::Color::Black, PAWN);
        
    }
    blackPieces[8] = Piece(0, 0, sf::Color::Black, ROOK);


    for (int i = 0; i < 8; i++) {
       
            whitePieces[i] = Piece(i, 6, sf::Color::White, PAWN);

    }
}

Piece* Game::FindPiece(int x, int y, Piece* whitePieces, Piece* blackPieces) {
    for (int i = 0; i <= 8; i++) {
        if ((whitePieces[i].x == x && whitePieces[i].y == y && whitePieces[i].isAlive) ||
            (blackPieces[i].x == x && blackPieces[i].y == y && blackPieces[i].isAlive)) {
            return (whitePieces[i].x == x && whitePieces[i].y == y) ? &whitePieces[i] : &blackPieces[i];
        }
    }
    return nullptr;
}

void Game::KillPiece(int x, int y, Piece* whitePieces, Piece* blackPieces) {
    Piece* pieceToKill = FindPiece(x, y, whitePieces, blackPieces);
    if (pieceToKill != nullptr) {
        pieceToKill->isAlive = false;
    }
}

std::vector<std::pair<int, int>> Game::GetAvailableJumps(Piece* piece, Piece* whitePieces, Piece* blackPieces) {
    std::vector<std::pair<int, int>> availableJumps;
    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (int i = 0; i < 4; i++) {
        int newX = piece->x + directions[i][0];
        int newY = piece->y + directions[i][1];


        // Ensure the jump is within bounds
        if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
            Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
            //std::cout << destPiece->x << ", " << destPiece->y << " " << destPiece->color.toInteger() << std::endl;

            // Only allow jumps over opponent pieces to an empty square
            if (destPiece != nullptr && destPiece->color != piece->color ) {
                // Ensure no backward jumps allowed
                if ((piece->color == sf::Color::Black && newY > piece->y) || (piece->color == sf::Color::White && newY < piece->y)) {
                    availableJumps.push_back({ newX, newY });
                }
            }
        }
    }
    return availableJumps;
}

std::vector<std::pair<int, int>> Game::GetAvailableMoves(Piece* piece, Piece* whitePieces, Piece* blackPieces) {
    std::vector<std::pair<int, int>> availableMoves;
    std::vector<std::pair<int, int>> availableJumps = GetAvailableJumps(piece, whitePieces, blackPieces);

    // If there are available jumps, return only the jumps
   /* if (!availableJumps.empty()) {
        //return availableJumps;
        //std::cout << "jump available\n";
    }*/

    // Define directions for movement
    std::vector<std::pair<int, int>> directions;

    // Add forward directions based on piece color
    if (piece->color == sf::Color::Black) {
        // black pieces move forward (downward)
        directions.push_back({ 0,1});  // forward-right

        if (piece->firstTurn) {
            directions.push_back({ 0, 2 }); // backward-left
        }
    }
    else if (piece->color == sf::Color::White) {
        // white pieces move forward (upward)
         // forward-left
        directions.push_back({ 0,-1 });  // forward-right

        // Allow backward directions if the piece is king
        if (piece->firstTurn) {
            directions.push_back({ 0,-2 }); // backward-left

        }
    }

    // Iterate through the possible directions and check for valid moves
    for (const auto& dir : directions) {
        int newX = piece->x + dir.first;
        int newY = piece->y + dir.second;

        if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
            Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
            if (destPiece == nullptr) {
                // Empty square - add as available move
                availableMoves.push_back({ newX, newY });
            }
        }
    }
    for (std::pair<int, int> jump : availableJumps) {
        availableMoves.push_back(jump);
        
    }

    return availableMoves;
}

void Game::MovePiece(Piece* piece, int newX, int newY, Piece* whitePieces, Piece* blackPieces, bool isJump) {
    // If it was a jump, kill the jumped piece
    

        //int midX = (piece->x + newX) / 2;
        //int midY = (piece->y + newY) / 2;
        KillPiece(newX, newY, whitePieces, blackPieces);
    
    // Update piece position
    piece->x = newX;
    piece->y = newY;

    // Crown the piece if it reaches the last row
    if (piece->firstTurn)
        piece->firstTurn = false;
    if ((piece->color == sf::Color::Black && piece->y == 7) ||
        (piece->color == sf::Color::White && piece->y == 0)) {
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

void Game::ProcessTurn(int& turn, sf::Vector2i mousePos, Piece* whitePieces, Piece* blackPieces, int& selectedX, int& selectedY, bool& isPieceSelected, bool& pieceHasJumped) {
    int clickedX = mousePos.x / 75;
    int clickedY = mousePos.y / 75;

    if (isPieceSelected) {
        Piece* selectedPiece = FindPiece(selectedX, selectedY, whitePieces, blackPieces);

        // Check if the clicked position is the same as the selected piece's position
        if (clickedX == selectedX && clickedY == selectedY) {
                isPieceSelected = false;
                selectedX = -1;
                selectedY = -1;
                pieceHasJumped = false;
            return;
        }

        // Process the move
        std::vector<std::pair<int, int>> availableMoves = GetAvailableMoves(selectedPiece, whitePieces, blackPieces);
        bool validMove = false;
        bool isJump = false;

        // Check if the clicked position is a valid move
        for (const auto& move : availableMoves) {
            if (move.first == clickedX && move.second == clickedY) {
                validMove = true;
                break;
            }
        }

        if (validMove) {
            MovePiece(selectedPiece, clickedX, clickedY, whitePieces, blackPieces, isJump);

            
                // Switch turns if there are no further jumps
                turn = 1 - turn;
                isPieceSelected = false;
                pieceHasJumped = false;
            
        }
    }
    else {
        // Select a piece
        Piece* clickedPiece = FindPiece(clickedX, clickedY, whitePieces, blackPieces);
        if (clickedPiece && clickedPiece->isAlive && clickedPiece->color == (turn == 0 ? sf::Color::White : sf::Color::Black)) {
            std::vector<std::pair<int, int>> availableMoves = GetAvailableMoves(clickedPiece, whitePieces, blackPieces);

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