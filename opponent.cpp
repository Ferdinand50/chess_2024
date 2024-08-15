#include "opponent.h"


Move AI_Handler::returnOpponentsMove(GameState &gamestate, const std::vector<Move> &legalMoves){
    Move bestMove;
    //TODO: change this accordingly
    float bestScore = 1000;
    float currentScore;

    for (const Move &move : legalMoves) {
        //Apply the move to the game state 
        makeMove(gamestate, move);

        //Evaluate the new game state
        //FIXME: it seem there is a bug with returnScore
        currentScore = returnScore(gamestate);
        LOG(currentScore);

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

AI_Handler::AI_Handler() {
}


float AI_Handler::returnScore(const GameState &gamestate) {
    float whiteScore = 0;
    float blackScore = 0;
    int piece;
    int pieceScore;
    int positionScore;

    //TODO:check if score is correct 
    //return score if checkmate
    if(gamestate.m_checkmate)
        return -1000;
    //return score if stalemate
    else if(gamestate.m_stalemate)
        return 0;

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
                    //TODO: enable position score
                    //whiteScore += pieceScore + positionScore*position_weight;
                    whiteScore += pieceScore;
                }
                //black pieces have a negative score
                else{
                    //TODO: enable position score
                    //negative since positionScore is positive
                    // blackScore += pieceScore - positionScore*position_weight;
                    blackScore += pieceScore;
                }
            }
        }
    }
    return whiteScore + blackScore;
}
