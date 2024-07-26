#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <iostream>
#include "Movement.h"
#include <stack>

//forward declaration
class Move;

//used to keep track of the pieces on the board in an efficent way
struct PieceInfo{
    int columm; //x
    int row; //y
    int type; //type of pieces in int

};

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
    bool m_whitesTurn;
    //logger for undoing moves
    std::stack<Move> moveLog;
    //keeps track of the active pieces for a faster way of itterating over the board
    //TODO: remove this or support full implementation
    std::vector<PieceInfo> m_whitePieces;
    std::vector<PieceInfo> m_blackPieces;
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


};

#endif // GAMESTATE_H
