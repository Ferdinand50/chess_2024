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
    int searchDepth = 4;
    //weight of position of pieces for evaluation score
    float position_weight = 0.1;
    //score for a checkmate
    int checkmateScore = 1000;
    //score for a stalemate
    int stalemateScore = 0;
    //stores best move of AI (used for advanced search algorithms)
    Move bestMoveAI;
    //map to get the score of a piece
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

    int blackPawnMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 2, 1, 1, 1, 1, 2, 1},
        {3, 3, 3, 4, 4, 3, 3, 3},
        {5, 5, 5, 6, 6, 5, 5, 5},
        {7, 7, 7, 7, 7, 7, 7, 7},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {3, 3, 3, 3, 3, 3, 3, 3}
    };

    int whitePawnMap[8][8] = {
        {3, 3, 3, 3, 3, 3, 3, 3},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {7, 7, 7, 7, 7, 7, 7, 7},
        {5, 5, 5, 6, 6, 5, 5, 5},
        {3, 3, 3, 4, 4, 3, 3, 3},
        {1, 2, 1, 1, 1, 1, 2, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int blackRookMap[8][8] = {
        {0, 0, 0, 2, 1, 4, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {2, 2, 2, 2, 2, 2, 2, 2}
    };

    int whiteRookMap[8][8] = {
        {2, 2, 2, 2, 2, 2, 2, 2},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 0, 2, 1, 4, 0, 0}
    };

    int blackKnightMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 3, 3, 3, 3, 2, 1},
        {1, 2, 3, 3, 3, 3, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int whiteKnightMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 3, 3, 3, 3, 2, 1},
        {1, 2, 3, 3, 3, 3, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int blackBishopMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {2, 1, 1, 2, 2, 1, 1, 2},
        {1, 1, 5, 3, 3, 5, 1, 1},
        {1, 4, 3, 3, 3, 3, 4, 1},
        {4, 2, 2, 2, 2, 2, 2, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    int whiteBishopMap[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {4, 2, 2, 2, 2, 2, 2, 4},
        {1, 4, 3, 3, 3, 3, 4, 1},
        {1, 1, 5, 3, 3, 5, 1, 1},
        {2, 1, 1, 2, 2, 1, 1, 2},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int blackQueenMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {2, 1, 1, 2, 2, 1, 1, 2},
        {1, 1, 5, 3, 3, 5, 1, 1},
        {1, 4, 3, 3, 3, 3, 4, 1},
        {4, 2, 2, 2, 2, 2, 2, 4},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {3, 3, 3, 3, 3, 3, 3, 3}
    };

    int whiteQueenMap[8][8] = {
        {3, 3, 3, 3, 3, 3, 3, 3},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {4, 2, 2, 2, 2, 2, 2, 4},
        {1, 4, 3, 3, 3, 3, 4, 1},
        {1, 1, 5, 3, 3, 5, 1, 1},
        {2, 1, 1, 2, 2, 1, 1, 2},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int blackKingMap[8][8] = {
        {1, 0, 3, 0, 0, 2, 4, 2},
        {0, 1, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int whiteKingMap[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1},
        {1, 0, 3, 0, 0, 2, 4, 2}
    };



public:
    //constructor
    AI_Handler();
    //gets best move for AI, without using a reference here
    Move returnBestMove(GameState gamestate, const std::vector<Move> legalMoves);
    //return score, modify bestMoveAI of AI_Handler (uses MinMax algorithm)
    float returnBestMoveMinMax(GameState &gamestate, const std::vector<Move> &legalMoves, int depth);
    //return score of certain board position
    float returnScore(const GameState &gamestate);
};





#endif // OPPONENT_H
