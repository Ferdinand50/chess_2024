#ifndef OPPONENT_H
#define OPPONENT_H

#include <map>

#include "Movement.h"
#include "gamestate.h"

class AI_Handler {
public:


private:
    //depth of search
    //TODO: use constructor
    int depth = 3;
    //weight of position of pieces for evaluation score
    float position_weight = 0.1;

    std::map<int, int> PieceScoreMap = {
        {whitePawn, 1},
        {whiteRook, 5},
        {whiteKnight, 3},
        {whiteBishop, 3},
        {whiteQueen, 9},
        {whiteKing, 0},
        {blackPawn, -1},
        {blackRook, -5},
        {blackKnight, -3},
        {blackBishop, -3},
        {blackQueen, -9},
        {blackKing, 0}
    };

    

public:
    //constructor
    AI_Handler();
    //returns the best move of the AI opponent
    Move returnOpponentsMove(const GameState &gamestate, const std::vector<Move> &legalMoves);
    //return score of certain board position
    float returnScore(const GameState &gamestate);
    //closing
    void close();

};





#endif // OPPONENT_H
