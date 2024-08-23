#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <iostream>
#include <stack>

#include "Movement.h"

//TODO: for release change this to 1
#define PR_DEBUG 0

#if PR_DEBUG == 0
#define LOG(x) std::cout<<x<<std::endl
#else 
#define LOG(x)
#endif

//TODO: rewrite codebase to support these defines
#define EMPTY 0
#define blackPawn 11
#define blackRook 12
#define blackKnight 13
#define blackBishop 14
#define blackQueen 15
#define blackKing 16
#define whitePawn 21
#define whiteRook 22
#define whiteKnight 23
#define whiteBishop 24
#define whiteQueen 25
#define whiteKing 26
#define Pawn 1
#define Rook 2
#define Knight 3
#define Bishop 4
#define Queen 5
#define King 6


//forward declaration
class Move;

class GameState 
{
private:

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
    //TODO: optimize the usage of vectors for example use m_pins.reserve() and use emplace_back instead of push_back
    // Create a list of vectors, each containing 4 integers for containing pins (y, x, pin_direction_y, pin_direction_x)
    mutable std::vector<std::vector<int>> m_pins; 
    // Create a list of vectors, each containing 4 integers for containing checks (y, x, pin_direction_y, pin_direction_x)
    mutable std::vector<std::vector<int>> m_checks;
    //TODO: this can be optimized, use different type of array make it 1d?
    //8x8 chess board
    int m_chessBoard[8][8] = {
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, blackKing, EMPTY, blackRook},
        {EMPTY, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {whiteQueen, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook}
    };

    int m_chessBoard_debug[8][8] = {
        {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook}
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
