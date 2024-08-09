#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <iostream>
#include <stack>

#include "Movement.h"


//forward declaration
class Move;

class GameState 
{
private:
    // Constants for piece types
    const int EMPTY = 0;
    const int BLACK_PAWN = 11;
    const int BLACK_ROOK = 12;
    const int BLACK_KNIGHT = 13;
    const int BLACK_BISHOP = 14;
    const int BLACK_QUEEN = 15;
    const int BLACK_KING = 16;
    const int WHITE_PAWN = 21;
    const int WHITE_ROOK = 22;
    const int WHITE_KNIGHT = 23;
    const int WHITE_BISHOP = 24;
    const int WHITE_QUEEN = 25;
    const int WHITE_KING = 26;

public:
    // which turn is it
    bool m_whitesTurn;
    // one player is in check
    mutable bool m_inCheck;
    //game is over
    mutable bool m_checkmate;
    //game is stalled
    mutable bool m_stalemate;
    //stores position of white King
    mutable std::vector<int> m_whiteKingPosition;
    //stores position of black King
    mutable std::vector<int> m_blackKingPosition;
    //logger for undoing moves
    std::stack<Move> m_moveLog;
    // Create a list of vectors, each containing 4 integers for containing pins (y, x, pin_direction_y, pin_direction_x)
    mutable std::vector<std::vector<int>> m_pins;
    // Create a list of vectors, each containing 4 integers for containing checks (y, x, pin_direction_y, pin_direction_x)
    mutable std::vector<std::vector<int>> m_checks;
    //8x8 chess board
    int m_chessBoard[8][8] = {
        {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK},
        {BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN},
        {WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK}
    };

public:
    // Constructor
    GameState();
    //returns True if there is a piece on the square and its turn
    bool isPieceTurn(int x, int y) const;
    // Debug function to print the chess board
    void printBoard() const;


};

#endif // GAMESTATE_H
