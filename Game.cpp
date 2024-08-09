#include "game.h"
#include "iostream"

void Game::Setup(Piece* whitePieces, Piece* blackPieces) {
    //Piece::loadStaticTextures();
    for (int i = 0; i < 8; i++) {
        
            blackPieces[i] = Piece(i, 1, sf::Color::Black, PAWN);
        
    }
    blackPieces[8] = Piece(0, 0, sf::Color::Black, ROOK);
    blackPieces[9] = Piece(7,0, sf::Color::Black, ROOK);
    blackPieces[10] = Piece(6, 0, sf::Color::Black, KNIGHT);
    blackPieces[11] = Piece(1,0, sf::Color::Black, KNIGHT);
    blackPieces[12] = Piece(2, 0, sf::Color::Black, BISHOP);
    blackPieces[13] = Piece(5,0, sf::Color::Black, BISHOP);
    blackPieces[14] = Piece(4, 0, sf::Color::Black, KING);
    blackPieces[15] = Piece(3,0, sf::Color::Black, QUEEN);

    for (int i = 0; i < 8; i++) {
       
            whitePieces[i] = Piece(i, 6, sf::Color::White, PAWN);

    }
    whitePieces[8] = Piece(0, 7, sf::Color::White, ROOK);
    whitePieces[9] = Piece(7, 7, sf::Color::White, ROOK);
    whitePieces[10] = Piece(6, 7, sf::Color::White, KNIGHT);
    whitePieces[11] = Piece(1, 7, sf::Color::White, KNIGHT);
    whitePieces[12] = Piece(2, 7, sf::Color::White, BISHOP);
    whitePieces[13] = Piece(5, 7, sf::Color::White, BISHOP);
    whitePieces[14] = Piece(4, 7, sf::Color::White, KING);
    whitePieces[15] = Piece(3, 7, sf::Color::White, QUEEN);
}

Piece* Game::FindPiece(int x, int y, Piece* whitePieces, Piece* blackPieces) {
    // Check for white pieces
    for (int i = 0; i < 16; i++) {
        if (whitePieces[i].x == x && whitePieces[i].y == y && whitePieces[i].isAlive) {
            return &whitePieces[i];
        }
    }
    // Check for black pieces
    for (int i = 0; i < 16; i++) {
        if (blackPieces[i].x == x && blackPieces[i].y == y && blackPieces[i].isAlive) {
            return &blackPieces[i];
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

    if (piece->pieceType == KING) {
        // King movement logic: one square in any direction
        std::pair<int, int> directions[8] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

        for (const auto& dir : directions) {
            int newX = piece->x + dir.first;
            int newY = piece->y + dir.second;

            if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
                Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
                if (destPiece == nullptr || destPiece->color != piece->color) {
                    availableMoves.push_back({ newX, newY });
                }
            }
        }

        // Castling logic: only if King and Rook haven't moved
        if (piece->firstTurn && !piece->isKing) {
            // King-side castling (right)
            Piece* kingSideRook = FindPiece(7, piece->y, whitePieces, blackPieces);
            if (kingSideRook && kingSideRook->pieceType == ROOK && kingSideRook->firstTurn) {
                if (FindPiece(piece->x + 1, piece->y, whitePieces, blackPieces) == nullptr &&
                    FindPiece(piece->x + 2, piece->y, whitePieces, blackPieces) == nullptr) {
                    availableMoves.push_back({ piece->x + 2, piece->y });
                }
            }

            // Queen-side castling (left)
            Piece* queenSideRook = FindPiece(0, piece->y, whitePieces, blackPieces);
            if (queenSideRook && queenSideRook->pieceType == ROOK && queenSideRook->firstTurn) {
                if (FindPiece(piece->x - 1, piece->y, whitePieces, blackPieces) == nullptr &&
                    FindPiece(piece->x - 2, piece->y, whitePieces, blackPieces) == nullptr &&
                    FindPiece(piece->x - 3, piece->y, whitePieces, blackPieces) == nullptr) {
                    availableMoves.push_back({ piece->x - 2, piece->y });
                }
            }
        }
    }
    else if (piece->pieceType == ROOK) {
        // Rook movement logic: horizontal and vertical
        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        for (const auto& dir : directions) {
            int newX = piece->x;
            int newY = piece->y;

            while (true) {
                newX += dir.first;
                newY += dir.second;

                if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
                    Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
                    if (destPiece == nullptr) {
                        availableMoves.push_back({ newX, newY });
                    }
                    else if (destPiece->color != piece->color) {
                        availableMoves.push_back({ newX, newY });
                        break;  // Rook can't jump over pieces
                    }
                    else {
                        break;  // Blocked by a piece of the same color
                    }
                }
                else {
                    break;  // Out of bounds
                }
            }
        }
    }
    else if (piece->pieceType == BISHOP) {
        // Bishop movement logic: diagonals
        std::pair<int, int> directions[4] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

        for (const auto& dir : directions) {
            int newX = piece->x;
            int newY = piece->y;

            while (true) {
                newX += dir.first;
                newY += dir.second;

                if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
                    Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
                    if (destPiece == nullptr) {
                        availableMoves.push_back({ newX, newY });
                    }
                    else if (destPiece->color != piece->color) {
                        availableMoves.push_back({ newX, newY });
                        break;  // Bishop can't jump over pieces
                    }
                    else {
                        break;  // Blocked by a piece of the same color
                    }
                }
                else {
                    break;  // Out of bounds
                }
            }
        }
    }
    else if (piece->pieceType == QUEEN) {
        // Queen movement logic: combination of Rook and Bishop
        std::pair<int, int> directions[8] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

        for (const auto& dir : directions) {
            int newX = piece->x;
            int newY = piece->y;

            while (true) {
                newX += dir.first;
                newY += dir.second;

                if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
                    Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
                    if (destPiece == nullptr) {
                        availableMoves.push_back({ newX, newY });
                    }
                    else if (destPiece->color != piece->color) {
                        availableMoves.push_back({ newX, newY });
                        break;  // Queen can't jump over pieces
                    }
                    else {
                        break;  // Blocked by a piece of the same color
                    }
                }
                else {
                    break;  // Out of bounds
                }
            }
        }
    }
    else if (piece->pieceType == KNIGHT) {
        // Knight movement logic: L-shaped moves
        std::pair<int, int> moves[8] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };

        for (const auto& move : moves) {
            int newX = piece->x + move.first;
            int newY = piece->y + move.second;

            if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
                Piece* destPiece = FindPiece(newX, newY, whitePieces, blackPieces);
                if (destPiece == nullptr || destPiece->color != piece->color) {
                    availableMoves.push_back({ newX, newY });
                }
            }
        }
    }
    else if (piece->pieceType == PAWN) {
        // Pawn movement logic
        if (piece->color == sf::Color::Black) {
            // Regular forward move
            if (FindPiece(piece->x, piece->y + 1, whitePieces, blackPieces) == nullptr) {
                availableMoves.push_back({ piece->x, piece->y + 1 });

                // Double move on first turn
                if (piece->firstTurn && FindPiece(piece->x, piece->y + 2, whitePieces, blackPieces) == nullptr) {
                    availableMoves.push_back({ piece->x, piece->y + 2 });
                }
            }

            // Capture diagonally left
            if (piece->x > 0) {
                Piece* captureLeft = FindPiece(piece->x - 1, piece->y + 1, whitePieces, blackPieces);
                if (captureLeft && captureLeft->color != piece->color) {
                    availableMoves.push_back({ piece->x - 1, piece->y + 1 });
                }
            }

            // Capture diagonally right
            if (piece->x < 7) {
                Piece* captureRight = FindPiece(piece->x + 1, piece->y + 1, whitePieces, blackPieces);
                if (captureRight && captureRight->color != piece->color) {
                    availableMoves.push_back({ piece->x + 1, piece->y + 1 });
                }
            }
        }
        else if (piece->color == sf::Color::White) {
            // Regular forward move
            if (FindPiece(piece->x, piece->y - 1, whitePieces, blackPieces) == nullptr) {
                availableMoves.push_back({ piece->x, piece->y - 1 });

                // Double move on first turn
                if (piece->firstTurn && FindPiece(piece->x, piece->y - 2, whitePieces, blackPieces) == nullptr) {
                    availableMoves.push_back({ piece->x, piece->y - 2 });
                }
            }

            // Capture diagonally left
            if (piece->x > 0) {
                Piece* captureLeft = FindPiece(piece->x - 1, piece->y - 1, whitePieces, blackPieces);
                if (captureLeft && captureLeft->color != piece->color) {
                    availableMoves.push_back({ piece->x - 1, piece->y - 1 });
                }
            }

            // Capture diagonally right
            if (piece->x < 7) {
                Piece* captureRight = FindPiece(piece->x + 1, piece->y - 1, whitePieces, blackPieces);
                if (captureRight && captureRight->color != piece->color) {
                    availableMoves.push_back({ piece->x + 1, piece->y - 1 });
                }
            }
        }
    }

    return availableMoves;
}


    // Optional: filter out moves that would put the player's own king in check
    // (this logic was discussed earlier, and should be included to ensure valid moves)






void Game::MovePiece(Piece* piece, int newX, int newY, Piece* whitePieces, Piece* blackPieces, bool isJump) {
    // Check if there is a piece at the destination
    Piece* capturedPiece = FindPiece(newX, newY, whitePieces, blackPieces);
    if (capturedPiece != nullptr && capturedPiece->color != piece->color) {
        // Mark the captured piece as not alive
        capturedPiece->isAlive = false;
    }

    // Handle Castling (if applicable)
    if (piece->pieceType == KING && abs(newX - piece->x) == 2) {
        // King-side castling
        if (newX > piece->x) {
            Piece* rook = FindPiece(7, piece->y, whitePieces, blackPieces);
            if (rook) {
                rook->x = newX - 1;  // Move the rook next to the king
            }
        }
        // Queen-side castling
        else if (newX < piece->x) {
            Piece* rook = FindPiece(0, piece->y, whitePieces, blackPieces);
            if (rook) {
                rook->x = newX + 1;  // Move the rook next to the king
            }
        }
    }

    // Update the moving piece's position
    piece->x = newX;
    piece->y = newY;

    // Mark the piece as having moved (for pawns, also disable firstTurn flag)
    piece->firstTurn = false;

    // Handle Pawn Promotion
    if (piece->pieceType == PAWN && ((piece->color == sf::Color::Black && piece->y == 7) ||
        (piece->color == sf::Color::White && piece->y == 0))) {
        piece->pieceType = QUEEN;  // Promote to Queen
        piece->setTexture();  // Update the texture to reflect the new Queen
    }
}


bool Game::IsKingInCheck(Piece* king, Piece* whitePieces, Piece* blackPieces) {
    Piece* opponentPieces = (king->color == sf::Color::White) ? blackPieces : whitePieces;

    for (int i = 0; i < 16; i++) {
        if (opponentPieces[i].isAlive) {
            std::vector<std::pair<int, int>> opponentMoves = GetAvailableMoves(&opponentPieces[i], whitePieces, blackPieces);
            for (const auto& move : opponentMoves) {
                if (move.first == king->x && move.second == king->y) {
                    return true;
                }
            }
        }
    }
    return false;
}
Piece* Game::FindPieceOfType(Type type, Piece* pieces) {
    for (int i = 0; i < 16; i++) {
        if (pieces[i].pieceType == type && pieces[i].isAlive) {
            return &pieces[i];
        }
    }
    return nullptr;
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

        for (const auto& move : availableMoves) {
            if (move.first == clickedX && move.second == clickedY) {
                validMove = true;
                break;
            }
        }

        if (validMove) {
            MovePiece(selectedPiece, clickedX, clickedY, whitePieces, blackPieces, false);

            // Switch turns
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

            if (!availableMoves.empty()) {
                selectedX = clickedX;
                selectedY = clickedY;
                isPieceSelected = true;
                pieceHasJumped = false;
            }
        }
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


