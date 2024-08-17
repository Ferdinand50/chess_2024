#include "opponent.h"

AI_Handler::AI_Handler() {
}

Move AI_Handler::returnOpponentsMove1StepLook(GameState &gamestate, const std::vector<Move> &legalMoves){
    Move bestMove;
    //TODO: change this accordingly
    float bestScore = 1000;
    float currentScore;

    //TODO: implement this correctly
    // //TODO:check if score is correct 
    // //return score if checkmate
    // if(gamestate.m_checkmate){
    //     LOG("[LOG]: Checkmate scoring.");
    //     return -checkmateScore;
    // }
    // //return score if stalemate
    // else if(gamestate.m_stalemate){
    //     LOG("[LOG]: Stalemate scoring.");
    //     return stalemateScore;
    // }

    for (const Move &move : legalMoves) {
        //Apply the move to the game state 
        makeMove(gamestate, move);

        //Evaluate the new game state
        currentScore = returnScore(gamestate);

        //Update bestMove if the current move has a better score
        if (currentScore < bestScore) {
            bestScore = currentScore;
            bestMove = move;
        }
        //undoMove
        undoMove(gamestate);
    }
    return bestMove;
}


Move AI_Handler::returnOpponentsMove2StepLook(GameState &gamestate, const std::vector<Move> &legalMoves){
    Move bestBlackMove;
    float blackMaxScore = -checkmateScore;
    int turnMultiplier = gamestate.m_whitesTurn ? 1 : -1;
    float currentScore;

    //black moves
    for (const Move &move : legalMoves) {
        //Apply the move to the game state 
        makeMove(gamestate, move);
        //TODO: remove theoreticalMoves
        std::vector<Move> legalMovesOpponent = legalMoves;
        std::vector<Move> theoreticalMoves = legalMoves;
        getLegalMoves(legalMovesOpponent, theoreticalMoves, gamestate);
        float whiteMaxScore = -checkmateScore;
        //white moves
        for (const Move &opponentMove : legalMovesOpponent) {
            turnMultiplier = 1;
            makeMove(gamestate, opponentMove);
            //evaluate
            if(gamestate.m_checkmate){
                currentScore = checkmateScore;
            }
            //if stalemate is possible score will set to neutral, there move will be only made if own score is worse than 0
            else if(gamestate.m_stalemate){
                currentScore = stalemateScore;
            }
            //score the current moves made
            else {
                currentScore = turnMultiplier * returnScore(gamestate);
            }
            if( currentScore > whiteMaxScore){
                whiteMaxScore = currentScore;
            }
            undoMove(gamestate);
        }
        turnMultiplier = -1;
        if (blackMaxScore < turnMultiplier * whiteMaxScore){
            blackMaxScore = turnMultiplier * whiteMaxScore;
            bestBlackMove = move;
        }
        undoMove(gamestate);
    }
    return bestBlackMove;
}



float AI_Handler::returnScore(const GameState &gamestate) {
    float whiteScore = 0;
    float blackScore = 0;
    int piece;
    int pieceScore;
    int positionScore;

    //evaluate the board
   for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            piece = gamestate.m_chessBoard[y][x];
            //piece detected
            if(piece!=EMPTY){
                pieceScore = PieceScoreMap[piece];
                
                //get score of position
                if (piece == whitePawn) {
                    positionScore = whitePawnMap[y][x];
                } else if (piece == blackPawn) {
                    positionScore = blackPawnMap[y][x];
                } else if (piece == whiteRook) {
                    positionScore = whiteRookMap[y][x];
                } else if (piece == blackRook) {
                    positionScore = blackRookMap[y][x];
                } else if (piece == whiteKnight) {
                    positionScore = whiteKnightMap[y][x];
                } else if (piece == blackKnight) {
                    positionScore = blackKnightMap[y][x];
                } else if (piece == whiteBishop) {
                    positionScore = whiteBishopMap[y][x];
                } else if (piece == blackBishop) {
                    positionScore = blackBishopMap[y][x];
                } else if (piece == whiteQueen) {
                    positionScore = whiteQueenMap[y][x];
                } else if (piece == blackQueen) {
                    positionScore = blackQueenMap[y][x];
                } else if (piece == whiteKing) {
                    positionScore = whiteKingMap[y][x];
                } else if (piece == blackKing) {
                    positionScore = blackKingMap[y][x];
                }

                //white pieces have a positive score
                if (pieceScore>0){
                    whiteScore += pieceScore + positionScore*position_weight;
                    //whiteScore += pieceScore;
                }
                //black pieces have a negative score
                else{
                    //negative since positionScore is positive
                    blackScore += pieceScore - positionScore*position_weight;
                    //blackScore += pieceScore;
                }
            }
        }
    }
    return whiteScore + blackScore;
}
