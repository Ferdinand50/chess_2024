#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <vector>
#include <set>
#include <utility> 

#include <string.h>
#include "gamestate.h"

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
    //constructor
    Move(const GameState &gamestate, MoveCoord moveCoord);
    //check if move is in legalMoves
    bool isLegal(std::vector<Move> const &legalMoves);
    //closes the move
    void close();
};

//makes a move
void makeMove(GameState &gamestate, Move move);
//undoes the latest move
void undoMove(GameState &gamestate);
//gets the valid moves for the current gamestate
void getLegalMoves(std::vector<Move> &legalMoves, std::vector<Move> &theoreticalMoves, const GameState &gamestate);
//gets the theoretical moves of each piece
void getTheoreticalMoves(std::vector<Move> &theoreticalMoves, const GameState &gamestate);
//get moves of pawns
void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of knights
void getKnightMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of rooks
void getRookMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of bishops
void getBishopMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of Queens
void getQueenMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//get moves of Kings
void getKingMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y);
//check if current gamestate is in check and if certain pieces are pinned
void checkForPinsAndChecks(const GameState &gamestate);
//return the type of a piece as int
int getPieceType(const GameState &gamestate, int x, int y);
//checks if the game is over
void CheckmateandStalemate(const std::vector<Move> &legalMoves, const GameState &gamestate);





#endif