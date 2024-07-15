#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <string.h>
#include "gamestate.h"

using namespace std;

struct MoveCoord
{
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
};


class Move
{
public:
    int m_pieceMoved;
    int m_pieceTaken;
    int m_start_x;
    int m_start_y;
    int m_end_x;
    int m_end_y;


private:
    
    

public:
    //TODO: Use reference
    Move(int const chessBoard[8][8], MoveCoord moveCoord);
    void close();
};


void makeMove(int (*chessBoard)[8][8], Move move);

//int return_piece_type(int MoveSelected[2], unsigned long long bitboard[12]);



#endif