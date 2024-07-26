#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <string.h>
#include "gamestate.h"
#include <vector>

using namespace std;

//forward declaration
class GameState;

struct MoveCoord{
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
};


class Move{
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
    //check if move is in legalMoves
    bool isLegal(std::vector<Move> const &legalMoves);
    void close();
};

//makes a move
void makeMove(int (&chessBoard)[8][8], Move move);
//gets the valid moves for the current gamestate
void getLegalMoves(std::vector<Move> &legalMoves, const GameState &gamestate);
//Get moves of pawns
void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of knights
void getKnightMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);





#endif