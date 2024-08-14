#ifndef OPPONENT_H
#define OPPONENT_H

#include "Movement.h"

class AI_Handler {
public:


private:
    //depth of search
    //TODO: use constructor
    int depth = 3;

    

public:
    //constructor
    AI_Handler();
    //returns the best move of the AI opponent
    Move returnOpponentsMove(const GameState &gamestate, const std::vector<Move> &legalMoves);
    //closing
    void close();

};





#endif // OPPONENT_H
